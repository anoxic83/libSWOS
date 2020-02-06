#pragma once
#define SWSAPI


#define SWS_TEAM_PREMIER 0
#define SWS_TEAM_FIRST 1
#define SWS_TEAM_SECOND 2
#define SWS_TEAM_THIRD 3
#define SWS_TEAM_NONLEAGUE 4

#define SWS_ATTRIBUTTE_PASSING 0
#define SWS_ATTRIBUTTE_SHOTING 1
#define SWS_ATTRIBUTTE_HEADING 2
#define SWS_ATTRIBUTTE_TACKLING 3
#define SWS_ATTRIBUTTE_BALLCONTROL 4
#define SWS_ATTRIBUTTE_SPEED 5
#define SWS_ATTRIBUTTE_FINISHING 6

const int SWSValuesStars[] = { 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 7, 7,
                              7, 7, 7, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10};

const std::string SWSValuesStr[] = {    "25K-", "25K", "30K", "40K", "50K", "65K", "75K", "85K", "100K", "110K", "130K",
    "150K", "160K", "180K", "200K", "250K", "300K", "350K", "450K", "500K", "550K",
    "600K", "650K", "700K", "750K", "800K", "850K", "950K", "1M", "1.1M", "1.3M",
    "1.5M", "1.6M", "1.8M", "1.9M", "2M", "2.25M", "2.75M", "3M", "3.5M", "4.5M",
    "5M", "6M", "7M", "8M", "9M", "10M", "12M", "15M", "15M+"
};

const std::string SWSNationalityStr[] = {
    "ALB", "AUT", "BEL", "BUL", "CRO", "CYP", "TCH", "DEN", "ENG", "EST", "FAR", "FIN",
    "FRA", "GER", "GRE", "HUN", "ICE", "ISR", "ITA", "LAT", "LIT", "LUX", "MLT", "HOL",
    "NIR", "NOR", "POL", "POR", "ROM", "RUS", "SMA", "SCO", "SLO", "SWE", "TUR", "UKR",
    "WAL", "SRB", "BLS", "SVK", "ESP", "ARM", "BOS", "AZB", "GEO", "SUI", "IRL", "MAC",
    "TKM", "LIE", "MOL", "CRC", "SAL", "GUA", "HON", "BHM", "MEX", "PAN", "USA", "BAH",
    "NIC", "BER", "JAM", "TRI", "CAN", "BAR", "ELS", "SVC", "ARG", "BOL", "BRA", "CHL",
    "COL", "ECU", "PAR", "SUR", "URU", "VEN", "GUY", "PER", "ALG", "SAF", "BOT", "BFS",
    "BUR", "LES", "ZAI", "ZAM", "GHA", "SEN", "CIV", "TUN", "MLI", "MDG", "CMR", "CHD",
    "UGA", "LIB", "MOZ", "KEN", "SUD", "SWA", "ANG", "TOG", "ZIM", "EGY", "TAN", "NIG",
    "ETH", "GAB", "SIE", "BEN", "CON", "GUI", "SRL", "MAR", "GAM", "MLW", "JAP", "TAI",
    "IND", "BAN", "BRU", "IRA", "JOR", "SRI", "SYR", "KOR", "IRN", "VIE", "MLY", "SAU",
    "YEM", "KUW", "LAO", "NKR", "OMA", "PAK", "PHI", "CHN", "SGP", "MAU", "MYA", "PAP",
    "TAD", "UZB", "QAT", "UAE", "AUS", "NZL", "FIJ", "SOL", "CUS"
    };

const std::string SWSPositionStr[] = {"GK","RB","LB","D","RW","LW","M","A"};

const std::string SWSTeamFileNames[] = {
    // EUROPE
      "TEAM.000", "TEAM.001", "TEAM.076", "TEAM.002", "TEAM.003", "TEAM.004", "TEAM.005", "TEAM.006", "TEAM.007",
      "TEAM.008", "TEAM.010", "TEAM.011", "TEAM.012", "TEAM.013", "TEAM.014", "TEAM.015", "TEAM.016", "TEAM.017", "TEAM.018", "TEAM.019", "TEAM.020",
      "TEAM.021", "TEAM.022", "TEAM.023", "TEAM.024", "TEAM.025", "TEAM.026", "TEAM.027", "TEAM.028", "TEAM.029", "TEAM.030", "TEAM.031", "TEAM.032",
      "TEAM.033", "TEAM.078", "TEAM.034", "TEAM.035", "TEAM.036", "TEAM.037", "TEAM.038", "TEAM.039", "TEAM.040", "TEAM.041",
      // NORTH AMERICA
      "TEAM.051", "TEAM.060", "TEAM.073",
      // SOUTH AMERICA
      "TEAM.043", "TEAM.045", "TEAM.046", "TEAM.048", "TEAM.049", "TEAM.050", "TEAM.064", "TEAM.065", "TEAM.066", "TEAM.071", "TEAM.077", 
      // AFRICA
      "TEAM.042", "TEAM.079", "TEAM.069",
      // ASIA
      "TEAM.075", "TEAM.055", "TEAM.067",
      // OCEANIA
      "TEAM.044", "TEAM.062"
};    
const std::string SWSTeamFileCoutries[] = {
      "Albania", "Austria", "Belarus", "Belgium", "Bulgaria", "Croatia", "Cyprus", "Czech Republic", "Denmark",
      "England", "Estonia", "Faroe Islands", "Finland", "France", "Germany", "Greece", "Hungary", "Iceland", "Republic Ireland", "Israel", "Italy",
      "Latva", "Lithuana", "Luxemburg", "Matla", "Holland", "Northern Ireland", "Norway", "Poland", "Portugal", "Romania", "Russia", "SanMarino",
      "Scotland", "Slovakia", "Spain", "Sweden", "Switzerland", "Turkey", "Ukraine", "Wales", "Yugoslavia",
      // NORTH AMERICA
      "El Salvador", "Mexico", "United States",
      // SOUTH AMERICA
      "Argentina", "Bolivia", "Brazil", "Chile", "Colombia", "Ecuador", "Paraguay", "Peru", "Surinam", "Uruguay", "Russia", "Venezuela",
      // AFRICA
      "Algeria", "Ghana", "South Africa",
      // ASIA
      "India", "Japan", "Taiwan",
      // OCEANIA
      "Australia", "New Zealand"

};
