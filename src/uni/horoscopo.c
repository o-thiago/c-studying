#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static constexpr int MAX_DAYS_IN_MONTH = 31;
static constexpr int DAYS_IN_FEBRUARY_LEAP = 29;
static constexpr int DAYS_IN_FEBRUARY_NON_LEAP = 28;
static constexpr int DAYS_IN_SHORT_MONTH = 30;
static constexpr int DAYS_IN_LONG_MONTH = 31;
static constexpr int TM_YEAR_BASE = 1900;

enum month {
	month_jan = 1,
	month_feb,
	month_mar,
	month_apr,
	month_may,
	month_jun,
	month_jul,
	month_aug,
	month_sep,
	month_oct,
	month_nov,
	month_dec,
};

struct [[maybe_unused]] month_day {
	enum month month;
	int day;
};

struct [[maybe_unused]] time_point {
	int day;
	enum month month;
	int year;
};

enum element { element_water, element_fire, element_earth, element_air };

enum zodiac_sign {
	sign_aries,
	sign_taurus,
	sign_gemini,
	sign_cancer,
	sign_leo,
	sign_virgo,
	sign_libra,
	sign_scorpio,
	sign_sagittarius,
	sign_capricorn,
	sign_aquarius,
	sign_pisces,
	sign_count,
};

struct [[maybe_unused]] zodiac_descriptor {
	enum zodiac_sign sign;
	enum element element;
	struct month_day begin_date;
	struct month_day end_date;
	char description[BUFSIZ];
};

enum program_option {
	option_load_zodiac,
	option_show_zodiac,
	option_register_new_user,
	option_show_last_user_zodiac_sign,
	option_show_last_user_age,
	option_exit,
	option_count,
};

struct [[maybe_unused]] zodiac_user {
	char name[BUFSIZ];
	struct month_day birth_month_day;
	int birth_year;
};

struct [[maybe_unused]] program_state {
	struct time_point current_time;
	struct zodiac_descriptor descriptors[sign_count];
	struct zodiac_user current_user;
	bool loaded_descriptors;
	bool loaded_current_user;
};

static void output_program_menu(void);
static void output_zodiac_calendar(const struct zodiac_descriptor *descriptors);

static bool warn_not_registered_user(bool registered_user);
static bool warn_not_loaded_descriptors(bool loaded_descriptors);
static bool warn_get_current_time_failure(struct time_point *current_time);

static bool try_read_program_option(char *buffer, size_t buffer_size,
									enum program_option *option);
static bool handle_program_option(enum program_option option,
								  struct program_state *state, char *buffer,
								  size_t buffer_size);
static void load_zodiac_descriptors(struct zodiac_descriptor *descriptors);
static bool try_register_zodiac_user(char *buffer, size_t buffer_size,
									 struct zodiac_user *user,
									 const struct time_point *current_time);
static bool try_get_current_time(struct time_point *current_time);

static int zodiac_user_get_age(const struct zodiac_user *user,
							   const struct time_point *current_time);
static bool
try_zodiac_user_get_sign(const struct zodiac_user *user,
						 const struct zodiac_descriptor *descriptors,
						 enum zodiac_sign *zodiac_sign);

static bool month_day_is_after_or_equal(const struct month_day *date,
										const struct month_day *other);
static bool month_day_is_before_or_equal(const struct month_day *date,
										 const struct month_day *other);
static bool month_day_is_between(const struct month_day *date,
								 const struct month_day *begin,
								 const struct month_day *end);
static int month_get_days_count(enum month month, int year);

static const char *month_get_name(enum month month);
static const char *element_get_name(enum element element);
static const char *zodiac_sign_get_name(enum zodiac_sign zodiac_sign);

static bool try_read_int(char *buffer, size_t buffer_size, int *out_value);

int main(void)
{
	struct program_state state = {0};
	char input_buffer[BUFSIZ];

	puts("Bem vindo ao programa de horóscopos!");
	while (true) {
		enum program_option option = option_count;
		if (warn_get_current_time_failure(&state.current_time)) continue;

		output_program_menu();
		if (!try_read_program_option(input_buffer, sizeof(input_buffer),
									 &option))
			continue;

		if (!handle_program_option(option, &state, input_buffer,
								   sizeof(input_buffer)))
			break;
	}

	return EXIT_SUCCESS;
}

static void output_program_menu(void)
{
	static const char *options[option_count] = {
		"Carregar calendário de horóscopos", "Exibir calendário de horóscopos",
		"Registrar uma nova pessoa",		 "Exibir signo da última pessoa",
		"Exibir idade da última pessoa",	 "Sair"};

	for (int i = 0; i < option_count; ++i)
		printf("[%d] - %s\n", i + 1, options[i]);
}

static void output_zodiac_calendar(const struct zodiac_descriptor *descriptors)
{
	puts("Calendário de horóscopos:\n");
	for (int i = 0; i < sign_count; ++i) {
		const struct zodiac_descriptor *descriptor = &descriptors[i];

		printf("%s (%s): %02d de %s até %02d de %s\n"
			   "Descrição: %s\n\n",
			   zodiac_sign_get_name(descriptor->sign),
			   element_get_name(descriptor->element),
			   descriptor->begin_date.day,
			   month_get_name(descriptor->begin_date.month),
			   descriptor->end_date.day,
			   month_get_name(descriptor->end_date.month),
			   descriptor->description);
	}
}

static bool warn_not_registered_user(const bool registered_user)
{
	if (registered_user) return false;
	puts("Por favor registre um usuário antes de chamar essa função!");
	return true;
}

static bool warn_not_loaded_descriptors(const bool loaded_descriptors)
{
	if (loaded_descriptors) return false;

	puts("Por favor carregue o calendário de horóscopos antes de "
		 "chamar essa função!");
	return true;
}

static bool warn_get_current_time_failure(struct time_point *current_time)
{
	if (try_get_current_time(current_time)) return false;

	puts("Falha ao ler data atual!");
	return true;
}

static bool try_read_program_option(char *buffer, const size_t buffer_size,
									enum program_option *option)
{
	if (fputs("Digite a opção: ", stdout) == EOF) return false;

	int raw_option = -1;
	if (!try_read_int(buffer, buffer_size, &raw_option)) return false;

	*option = (enum program_option)(raw_option - 1);
	return true;
}

static bool handle_program_option(const enum program_option option,
								  struct program_state *state, char *buffer,
								  const size_t buffer_size)
{
	switch (option) {
	case option_load_zodiac:
		if (state->loaded_descriptors) {
			puts("O calendário de horóscopo já está carregado. Então nada foi "
				 "realizado!");
			break;
		}

		load_zodiac_descriptors(state->descriptors);
		state->loaded_descriptors = true;
		break;
	case option_show_zodiac:
		if (warn_not_loaded_descriptors(state->loaded_descriptors)) break;
		output_zodiac_calendar(state->descriptors);
		break;
	case option_register_new_user:

		const bool read_user = try_register_zodiac_user(
			buffer, buffer_size, &state->current_user, &state->current_time);

		if (!read_user) {
			puts("Falha ao registrar usuário!");
			break;
		}

		state->loaded_current_user = true;
		break;
	case option_show_last_user_zodiac_sign:
		if (warn_not_loaded_descriptors(state->loaded_descriptors) ||
			warn_not_registered_user(state->loaded_current_user))
			break;

		enum zodiac_sign current_user_sign = sign_count;
		if (!try_zodiac_user_get_sign(&state->current_user, state->descriptors,
									  &current_user_sign)) {
			puts("Falha ao identificar signo do usuário!");
			break;
		}

		printf("O signo do(a) %s é %s\n", state->current_user.name,
			   zodiac_sign_get_name(current_user_sign));
		break;
	case option_show_last_user_age:
		if (warn_not_registered_user(state->loaded_current_user)) break;

		printf("A idade do(a) %s é %d\n", state->current_user.name,
			   zodiac_user_get_age(&state->current_user, &state->current_time));
		break;
	case option_exit:
		return false;
	case option_count:
		puts("Digite uma opção válida por favor!");
		break;
	}

	return true;
}

static void load_zodiac_descriptors(struct zodiac_descriptor *descriptors)
{
	const struct zodiac_descriptor data[sign_count] = {
		[sign_aries] = {sign_aries,
						element_fire,
						{month_mar, 21},
						{month_apr, 19},
						"Corajoso e entusiasmado."},
		[sign_taurus] = {sign_taurus,
						 element_earth,
						 {month_apr, 20},
						 {month_may, 20},
						 "Paciente e confiável."},
		[sign_gemini] = {sign_gemini,
						 element_air,
						 {month_may, 21},
						 {month_jun, 20},
						 "Adaptável e versátil."},
		[sign_cancer] = {sign_cancer,
						 element_water,
						 {month_jun, 21},
						 {month_jul, 22},
						 "Emocional e protetor."},
		[sign_leo] = {sign_leo,
					  element_fire,
					  {month_jul, 23},
					  {month_aug, 22},
					  "Generoso e criativo."},
		[sign_virgo] = {sign_virgo,
						element_earth,
						{month_aug, 23},
						{month_sep, 22},
						"Analítico e prático."},
		[sign_libra] = {sign_libra,
						element_air,
						{month_sep, 23},
						{month_oct, 22},
						"Diplomático e sociável."},
		[sign_scorpio] = {sign_scorpio,
						  element_water,
						  {month_oct, 23},
						  {month_nov, 21},
						  "Determinado e apaixonado."},
		[sign_sagittarius] = {sign_sagittarius,
							  element_fire,
							  {month_nov, 22},
							  {month_dec, 21},
							  "Otimista e amante da liberdade."},
		[sign_capricorn] = {sign_capricorn,
							element_earth,
							{month_dec, 22},
							{month_jan, 19},
							"Ambicioso e disciplinado."},
		[sign_aquarius] = {sign_aquarius,
						   element_air,
						   {month_jan, 20},
						   {month_feb, 18},
						   "Original e independente."},
		[sign_pisces] = {sign_pisces,
						 element_water,
						 {month_feb, 19},
						 {month_mar, 20},
						 "Compassivo e intuitivo."}};

	for (int i = 0; i < sign_count; ++i) descriptors[i] = data[i];
}

static bool try_register_zodiac_user(char *buffer, const size_t buffer_size,
									 struct zodiac_user *user,
									 const struct time_point *current_time)
{
	struct zodiac_user new_user;

	if (fputs("Digite o nome do usuário: ", stdout) == EOF) return false;
	if (!fgets(new_user.name, BUFSIZ, stdin)) return false;

	new_user.name[strcspn(new_user.name, "\n")] = '\0';
	if (fputs("Digite o dia de nascimento do usuário: ", stdout) == EOF)
		return false;

	if (!try_read_int(buffer, buffer_size, &new_user.birth_month_day.day))
		return false;

	if (new_user.birth_month_day.day < 1 ||
		new_user.birth_month_day.day > MAX_DAYS_IN_MONTH) {
		puts("Dia inválido!");
		return false;
	}

	if (fputs("Digite o mês de nascimento do usuário: ", stdout) == EOF)
		return false;

	int raw_month = 0;
	if (!try_read_int(buffer, buffer_size, &raw_month)) return false;

	if (raw_month < month_jan || raw_month > month_dec) {
		puts("Mês inválido!");
		return false;
	}

	const enum month birth_month = (enum month)raw_month;

	if (fputs("Digite o ano de nascimento do usuário: ", stdout) == EOF)
		return false;
	if (!try_read_int(buffer, buffer_size, &new_user.birth_year)) return false;

	if (new_user.birth_month_day.day >
		month_get_days_count(birth_month, new_user.birth_year)) {
		puts("Dia inválido para o mês e ano informado!");
		return false;
	}

	new_user.birth_month_day.month = birth_month;
	if (new_user.birth_year > current_time->year ||
		(new_user.birth_year == current_time->year &&
		 (new_user.birth_month_day.month > current_time->month ||
		  (new_user.birth_month_day.month == current_time->month &&
		   new_user.birth_month_day.day > current_time->day)))) {
		puts("A data de nascimento não pode ser maior que a data atual!");
		return false;
	}

	*user = new_user;
	return true;
}

static bool try_get_current_time(struct time_point *current_time)
{
	time_t raw_time = 0;
	if (time(&raw_time) == -1) return false;

	struct tm local_time;
#ifdef _WIN32
	if (localtime_s(&local_time, &raw_time) != 0) return false;
#else
	if (localtime_r(&raw_time, &local_time) == nullptr) return false;
#endif

	current_time->year = local_time.tm_year + TM_YEAR_BASE;
	current_time->month = (enum month)(local_time.tm_mon + 1);
	current_time->day = local_time.tm_mday;

	return true;
}

static int zodiac_user_get_age(const struct zodiac_user *user,
							   const struct time_point *current_time)
{
	int user_age = current_time->year - user->birth_year;
	const enum month birth_month = user->birth_month_day.month;

	if (current_time->month < birth_month ||
		(current_time->month == birth_month &&
		 current_time->day < user->birth_month_day.day))
		user_age--;

	return user_age;
}

static bool
try_zodiac_user_get_sign(const struct zodiac_user *user,
						 const struct zodiac_descriptor *descriptors,
						 enum zodiac_sign *zodiac_sign)
{
	for (int i = 0; i < sign_count; ++i) {
		const struct zodiac_descriptor *current_descriptor = &descriptors[i];
		if (month_day_is_between(&user->birth_month_day,
								 &current_descriptor->begin_date,
								 &current_descriptor->end_date)) {
			*zodiac_sign = current_descriptor->sign;
			return true;
		}
	}

	return false;
}

static bool month_day_is_after_or_equal(const struct month_day *date,
										const struct month_day *other)
{
	return (date->month > other->month ||
			(date->month == other->month && date->day >= other->day)) != 0;
}

static bool month_day_is_before_or_equal(const struct month_day *date,
										 const struct month_day *other)
{
	return (date->month < other->month ||
			(date->month == other->month && date->day <= other->day)) != 0;
}

static bool month_day_is_between(const struct month_day *date,
								 const struct month_day *begin,
								 const struct month_day *end)
{
	/* Intervalo comum no mesmo ano, por exemplo, 21/03 até 19/04. */
	if (month_day_is_before_or_equal(begin, end))
		return (month_day_is_after_or_equal(date, begin) &&
				month_day_is_before_or_equal(date, end)) != 0;

	/* Intervalo que vira o ano, por exemplo, 22/12 até 19/01. */
	return (month_day_is_after_or_equal(date, begin) ||
			month_day_is_before_or_equal(date, end)) != 0;
}

static int month_get_days_count(const enum month month, const int year)
{

	switch (month) {
	case month_feb: {
		const bool is_leap_year =
			(year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
		return is_leap_year ? DAYS_IN_FEBRUARY_LEAP : DAYS_IN_FEBRUARY_NON_LEAP;
	}
	case month_apr:
	case month_jun:
	case month_sep:
	case month_nov:
		return DAYS_IN_SHORT_MONTH;
	case month_jan:
	case month_mar:
	case month_may:
	case month_jul:
	case month_aug:
	case month_oct:
	case month_dec:
		return DAYS_IN_LONG_MONTH;
	}

	return 0;
}

static const char *month_get_name(const enum month month)
{
	static const char *names[] = {
		"Janeiro", "Fevereiro", "Março",	"Abril",   "Maio",	   "Junho",
		"Julho",   "Agosto",	"Setembro", "Outubro", "Novembro", "Dezembro"};
	return names[month - 1];
}

static const char *element_get_name(const enum element element)
{
	static const char *names[] = {"água", "fogo", "terra", "ar"};
	return names[element];
}

static const char *zodiac_sign_get_name(const enum zodiac_sign zodiac_sign)
{
	static const char *names[sign_count] = {
		"áries", "touro",	  "gêmeos",	   "câncer",	  "leão",	 "virgem",
		"libra", "escorpião", "sagitário", "capricórnio", "aquário", "peixes"};
	return names[zodiac_sign];
}

static bool try_read_int(char *buffer, const size_t buffer_size, int *out_value)
{
	if (buffer_size > INT_MAX) return false;
	if (!fgets(buffer, (int)buffer_size, stdin)) return false;

	char *end_ptr = nullptr;
	errno = 0;
	const long val = strtol(buffer, &end_ptr, 10);

	// Checagem de erros de conversão.
	if (end_ptr == buffer || errno == ERANGE || val > INT_MAX || val < INT_MIN)
		return false;

	// Verificamos se a string contém apenas espaços e não outros caractéres.
	while ((isspace)((unsigned char)*end_ptr)) end_ptr++;
	if (*end_ptr != '\0') return false;

	*out_value = (int)val;
	return true;
}
