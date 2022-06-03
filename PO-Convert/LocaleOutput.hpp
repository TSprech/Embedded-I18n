using cldr_t = std::u8string_view;

struct Symbols {
  cldr_t decimal;
  cldr_t group;
  cldr_t list;
  cldr_t percent_sign;
  cldr_t plus_sign;
  cldr_t minus_sign;
  cldr_t exponential;
  cldr_t superscripting_exponent;
  cldr_t infinity;
  cldr_t nan;
};

struct Delimiters {
  cldr_t quotation_start;
  cldr_t quotation_end;
  cldr_t alternate_quotation_start;
  cldr_t alternate_quotation_end;
};

struct Numbers {
    Symbols symbols;
};


<months>
					<monthContext type="format">
						<monthWidth type="abbreviated">
							<month type="1">Jan</month>

struct MonthWidth {
    std::array<cldr_t, 12> month;
};

struct MonthContext {
    MonthWidth abbreviated;
};

struct Months {
    MonthContext format;
};

struct CalendarType {
    Months months;
};

struct Calendars {
    CalendarType gregorian;
};

struct Dates {
    Calendars calendars;
};

struct Locale {
    Delimiters delimiters;
    Numbers numbers;
    Dates dates;
};

Locale en_US {
    .delimiters = {
      .quotation_start = u8"“"sv,
      .quotation_end = u8"”"sv,
      .alt_quotation_start = u8"‘"sv,
      .alt_quotation_end = u8"’"sv
    },

    .numbers = {
      .symbols = {
        .decimal = u8"."sv,
        .group = u8","sv,
        .list = u8";"sv,
        .percent_sign = u8"%"sv,
        .plus_sign = u8"+"sv,
        .minus_sign = u8"-"sv,
        .exponential = u8"E"sv,
        .superscripting_exponent = u8"×"sv,
        .per_mille = u8"‰"sv,
        .infinity = u8"∞"sv,
        .nan = u8"NaN"sv
      }
    },

    .dates {
      .calendars {
        .gregorian {
          .months {
            .format {
              .abbreviated {
                .month = { "Jan",
                           "Feb",
                           "Mar",
                           "Apr",
                           "May",
                           "Jun",
                           "Jul",
                           "Aug",
                           "Sep",
                           "Oct",
                           "Nov",
                           "Dec"
                }
              }
            }
          }
        }
      }
    }
};



std::array weekdays_shortened = {u8"Sun"sv,
                                 u8"Mon"sv,
                                 u8"Tue"sv,
                                 u8"Wed"sv,
                                 u8"Thu"sv,
                                 u8"Fri"sv,
                                 u8"Sat"sv};
auto am = u8"AM"sv;
auto pm = u8"PM"sv;
auto time_format_h_m_s = u8"h:mm:ss a"sv;
auto time_format_h_m = u8"h:mm a"sv;
