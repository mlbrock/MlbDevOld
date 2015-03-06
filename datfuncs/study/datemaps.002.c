/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts three integers representing year, month, and
								day to a JULIAN date.

	Revision History	:	1989-11-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1989 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

/*	*********************************************************************** */
/*	*********************************************************************** */
/* 	Necessary include files . . .														*/
/*	*********************************************************************** */

#include <stdlib.h>

#include "datfi.h"

/*	*********************************************************************** */

typedef struct {
	unsigned int year;
	JULIAN       j_year;
} DATFUNCS_DATE_MAP;

/* *********************************************************************** */
int    jultoymd_basic(JULIAN in_julian, int *out_year_ptr, int *out_month_ptr,
	int *out_day_ptr, unsigned int year_map_count,
	const DATFUNCS_DATE_MAP *year_map_list);
JULIAN ymdtojul_basic(int in_year, int in_month, int in_day,
	unsigned int year_map_count,
	const DATFUNCS_DATE_MAP *year_map_list);
int    DATFUNCS_CreateDateMap(unsigned int first_year, unsigned int last_year,
	int century_flag, unsigned int *date_map_count,
	DATFUNCS_DATE_MAP **date_map_list, char *error_text);
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */
#ifndef NARGS
static int                      DATFUNCS_CMP_DateMap(void *control_ptr,
	const DATFUNCS_DATE_MAP *ptr_1, const DATFUNCS_DATE_MAP *ptr_2,
	size_t data_length);
static const DATFUNCS_DATE_MAP *DATFUNCS_FIND_DateMap(
	unsigned int date_map_count, const DATFUNCS_DATE_MAP *date_map_list,
	JULIAN in_julian);
#else
static int                      DATFUNCS_CMP_DateMap();
static const DATFUNCS_DATE_MAP *DATFUNCS_FIND_DateMap();
#endif /* #ifndef NARGS */
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */
static const DATFUNCS_DATE_MAP DATFUNCS_YearMapList[] = {
	{ 1800, ((JULIAN)      -36524L) },
	{ 1801, ((JULIAN)      -36159L) },
	{ 1802, ((JULIAN)      -35794L) },
	{ 1803, ((JULIAN)      -35429L) },
	{ 1804, ((JULIAN)      -35064L) },
	{ 1805, ((JULIAN)      -34698L) },
	{ 1806, ((JULIAN)      -34333L) },
	{ 1807, ((JULIAN)      -33968L) },
	{ 1808, ((JULIAN)      -33603L) },
	{ 1809, ((JULIAN)      -33237L) },
	{ 1810, ((JULIAN)      -32872L) },
	{ 1811, ((JULIAN)      -32507L) },
	{ 1812, ((JULIAN)      -32142L) },
	{ 1813, ((JULIAN)      -31776L) },
	{ 1814, ((JULIAN)      -31411L) },
	{ 1815, ((JULIAN)      -31046L) },
	{ 1816, ((JULIAN)      -30681L) },
	{ 1817, ((JULIAN)      -30315L) },
	{ 1818, ((JULIAN)      -29950L) },
	{ 1819, ((JULIAN)      -29585L) },
	{ 1820, ((JULIAN)      -29220L) },
	{ 1821, ((JULIAN)      -28854L) },
	{ 1822, ((JULIAN)      -28489L) },
	{ 1823, ((JULIAN)      -28124L) },
	{ 1824, ((JULIAN)      -27759L) },
	{ 1825, ((JULIAN)      -27393L) },
	{ 1826, ((JULIAN)      -27028L) },
	{ 1827, ((JULIAN)      -26663L) },
	{ 1828, ((JULIAN)      -26298L) },
	{ 1829, ((JULIAN)      -25932L) },
	{ 1830, ((JULIAN)      -25567L) },
	{ 1831, ((JULIAN)      -25202L) },
	{ 1832, ((JULIAN)      -24837L) },
	{ 1833, ((JULIAN)      -24471L) },
	{ 1834, ((JULIAN)      -24106L) },
	{ 1835, ((JULIAN)      -23741L) },
	{ 1836, ((JULIAN)      -23376L) },
	{ 1837, ((JULIAN)      -23010L) },
	{ 1838, ((JULIAN)      -22645L) },
	{ 1839, ((JULIAN)      -22280L) },
	{ 1840, ((JULIAN)      -21915L) },
	{ 1841, ((JULIAN)      -21549L) },
	{ 1842, ((JULIAN)      -21184L) },
	{ 1843, ((JULIAN)      -20819L) },
	{ 1844, ((JULIAN)      -20454L) },
	{ 1845, ((JULIAN)      -20088L) },
	{ 1846, ((JULIAN)      -19723L) },
	{ 1847, ((JULIAN)      -19358L) },
	{ 1848, ((JULIAN)      -18993L) },
	{ 1849, ((JULIAN)      -18627L) },
	{ 1850, ((JULIAN)      -18262L) },
	{ 1851, ((JULIAN)      -17897L) },
	{ 1852, ((JULIAN)      -17532L) },
	{ 1853, ((JULIAN)      -17166L) },
	{ 1854, ((JULIAN)      -16801L) },
	{ 1855, ((JULIAN)      -16436L) },
	{ 1856, ((JULIAN)      -16071L) },
	{ 1857, ((JULIAN)      -15705L) },
	{ 1858, ((JULIAN)      -15340L) },
	{ 1859, ((JULIAN)      -14975L) },
	{ 1860, ((JULIAN)      -14610L) },
	{ 1861, ((JULIAN)      -14244L) },
	{ 1862, ((JULIAN)      -13879L) },
	{ 1863, ((JULIAN)      -13514L) },
	{ 1864, ((JULIAN)      -13149L) },
	{ 1865, ((JULIAN)      -12783L) },
	{ 1866, ((JULIAN)      -12418L) },
	{ 1867, ((JULIAN)      -12053L) },
	{ 1868, ((JULIAN)      -11688L) },
	{ 1869, ((JULIAN)      -11322L) },
	{ 1870, ((JULIAN)      -10957L) },
	{ 1871, ((JULIAN)      -10592L) },
	{ 1872, ((JULIAN)      -10227L) },
	{ 1873, ((JULIAN)       -9861L) },
	{ 1874, ((JULIAN)       -9496L) },
	{ 1875, ((JULIAN)       -9131L) },
	{ 1876, ((JULIAN)       -8766L) },
	{ 1877, ((JULIAN)       -8400L) },
	{ 1878, ((JULIAN)       -8035L) },
	{ 1879, ((JULIAN)       -7670L) },
	{ 1880, ((JULIAN)       -7305L) },
	{ 1881, ((JULIAN)       -6939L) },
	{ 1882, ((JULIAN)       -6574L) },
	{ 1883, ((JULIAN)       -6209L) },
	{ 1884, ((JULIAN)       -5844L) },
	{ 1885, ((JULIAN)       -5478L) },
	{ 1886, ((JULIAN)       -5113L) },
	{ 1887, ((JULIAN)       -4748L) },
	{ 1888, ((JULIAN)       -4383L) },
	{ 1889, ((JULIAN)       -4017L) },
	{ 1890, ((JULIAN)       -3652L) },
	{ 1891, ((JULIAN)       -3287L) },
	{ 1892, ((JULIAN)       -2922L) },
	{ 1893, ((JULIAN)       -2556L) },
	{ 1894, ((JULIAN)       -2191L) },
	{ 1895, ((JULIAN)       -1826L) },
	{ 1896, ((JULIAN)       -1461L) },
	{ 1897, ((JULIAN)       -1095L) },
	{ 1898, ((JULIAN)        -730L) },
	{ 1899, ((JULIAN)        -365L) },
	{ 1900, ((JULIAN)           0L) },
	{ 1901, ((JULIAN)         365L) },
	{ 1902, ((JULIAN)         730L) },
	{ 1903, ((JULIAN)        1095L) },
	{ 1904, ((JULIAN)        1460L) },
	{ 1905, ((JULIAN)        1826L) },
	{ 1906, ((JULIAN)        2191L) },
	{ 1907, ((JULIAN)        2556L) },
	{ 1908, ((JULIAN)        2921L) },
	{ 1909, ((JULIAN)        3287L) },
	{ 1910, ((JULIAN)        3652L) },
	{ 1911, ((JULIAN)        4017L) },
	{ 1912, ((JULIAN)        4382L) },
	{ 1913, ((JULIAN)        4748L) },
	{ 1914, ((JULIAN)        5113L) },
	{ 1915, ((JULIAN)        5478L) },
	{ 1916, ((JULIAN)        5843L) },
	{ 1917, ((JULIAN)        6209L) },
	{ 1918, ((JULIAN)        6574L) },
	{ 1919, ((JULIAN)        6939L) },
	{ 1920, ((JULIAN)        7304L) },
	{ 1921, ((JULIAN)        7670L) },
	{ 1922, ((JULIAN)        8035L) },
	{ 1923, ((JULIAN)        8400L) },
	{ 1924, ((JULIAN)        8765L) },
	{ 1925, ((JULIAN)        9131L) },
	{ 1926, ((JULIAN)        9496L) },
	{ 1927, ((JULIAN)        9861L) },
	{ 1928, ((JULIAN)       10226L) },
	{ 1929, ((JULIAN)       10592L) },
	{ 1930, ((JULIAN)       10957L) },
	{ 1931, ((JULIAN)       11322L) },
	{ 1932, ((JULIAN)       11687L) },
	{ 1933, ((JULIAN)       12053L) },
	{ 1934, ((JULIAN)       12418L) },
	{ 1935, ((JULIAN)       12783L) },
	{ 1936, ((JULIAN)       13148L) },
	{ 1937, ((JULIAN)       13514L) },
	{ 1938, ((JULIAN)       13879L) },
	{ 1939, ((JULIAN)       14244L) },
	{ 1940, ((JULIAN)       14609L) },
	{ 1941, ((JULIAN)       14975L) },
	{ 1942, ((JULIAN)       15340L) },
	{ 1943, ((JULIAN)       15705L) },
	{ 1944, ((JULIAN)       16070L) },
	{ 1945, ((JULIAN)       16436L) },
	{ 1946, ((JULIAN)       16801L) },
	{ 1947, ((JULIAN)       17166L) },
	{ 1948, ((JULIAN)       17531L) },
	{ 1949, ((JULIAN)       17897L) },
	{ 1950, ((JULIAN)       18262L) },
	{ 1951, ((JULIAN)       18627L) },
	{ 1952, ((JULIAN)       18992L) },
	{ 1953, ((JULIAN)       19358L) },
	{ 1954, ((JULIAN)       19723L) },
	{ 1955, ((JULIAN)       20088L) },
	{ 1956, ((JULIAN)       20453L) },
	{ 1957, ((JULIAN)       20819L) },
	{ 1958, ((JULIAN)       21184L) },
	{ 1959, ((JULIAN)       21549L) },
	{ 1960, ((JULIAN)       21914L) },
	{ 1961, ((JULIAN)       22280L) },
	{ 1962, ((JULIAN)       22645L) },
	{ 1963, ((JULIAN)       23010L) },
	{ 1964, ((JULIAN)       23375L) },
	{ 1965, ((JULIAN)       23741L) },
	{ 1966, ((JULIAN)       24106L) },
	{ 1967, ((JULIAN)       24471L) },
	{ 1968, ((JULIAN)       24836L) },
	{ 1969, ((JULIAN)       25202L) },
	{ 1970, ((JULIAN)       25567L) },
	{ 1971, ((JULIAN)       25932L) },
	{ 1972, ((JULIAN)       26297L) },
	{ 1973, ((JULIAN)       26663L) },
	{ 1974, ((JULIAN)       27028L) },
	{ 1975, ((JULIAN)       27393L) },
	{ 1976, ((JULIAN)       27758L) },
	{ 1977, ((JULIAN)       28124L) },
	{ 1978, ((JULIAN)       28489L) },
	{ 1979, ((JULIAN)       28854L) },
	{ 1980, ((JULIAN)       29219L) },
	{ 1981, ((JULIAN)       29585L) },
	{ 1982, ((JULIAN)       29950L) },
	{ 1983, ((JULIAN)       30315L) },
	{ 1984, ((JULIAN)       30680L) },
	{ 1985, ((JULIAN)       31046L) },
	{ 1986, ((JULIAN)       31411L) },
	{ 1987, ((JULIAN)       31776L) },
	{ 1988, ((JULIAN)       32141L) },
	{ 1989, ((JULIAN)       32507L) },
	{ 1990, ((JULIAN)       32872L) },
	{ 1991, ((JULIAN)       33237L) },
	{ 1992, ((JULIAN)       33602L) },
	{ 1993, ((JULIAN)       33968L) },
	{ 1994, ((JULIAN)       34333L) },
	{ 1995, ((JULIAN)       34698L) },
	{ 1996, ((JULIAN)       35063L) },
	{ 1997, ((JULIAN)       35429L) },
	{ 1998, ((JULIAN)       35794L) },
	{ 1999, ((JULIAN)       36159L) },
	{ 2000, ((JULIAN)       36524L) },
	{ 2001, ((JULIAN)       36890L) },
	{ 2002, ((JULIAN)       37255L) },
	{ 2003, ((JULIAN)       37620L) },
	{ 2004, ((JULIAN)       37985L) },
	{ 2005, ((JULIAN)       38351L) },
	{ 2006, ((JULIAN)       38716L) },
	{ 2007, ((JULIAN)       39081L) },
	{ 2008, ((JULIAN)       39446L) },
	{ 2009, ((JULIAN)       39812L) },
	{ 2010, ((JULIAN)       40177L) },
	{ 2011, ((JULIAN)       40542L) },
	{ 2012, ((JULIAN)       40907L) },
	{ 2013, ((JULIAN)       41273L) },
	{ 2014, ((JULIAN)       41638L) },
	{ 2015, ((JULIAN)       42003L) },
	{ 2016, ((JULIAN)       42368L) },
	{ 2017, ((JULIAN)       42734L) },
	{ 2018, ((JULIAN)       43099L) },
	{ 2019, ((JULIAN)       43464L) },
	{ 2020, ((JULIAN)       43829L) },
	{ 2021, ((JULIAN)       44195L) },
	{ 2022, ((JULIAN)       44560L) },
	{ 2023, ((JULIAN)       44925L) },
	{ 2024, ((JULIAN)       45290L) },
	{ 2025, ((JULIAN)       45656L) },
	{ 2026, ((JULIAN)       46021L) },
	{ 2027, ((JULIAN)       46386L) },
	{ 2028, ((JULIAN)       46751L) },
	{ 2029, ((JULIAN)       47117L) },
	{ 2030, ((JULIAN)       47482L) },
	{ 2031, ((JULIAN)       47847L) },
	{ 2032, ((JULIAN)       48212L) },
	{ 2033, ((JULIAN)       48578L) },
	{ 2034, ((JULIAN)       48943L) },
	{ 2035, ((JULIAN)       49308L) },
	{ 2036, ((JULIAN)       49673L) },
	{ 2037, ((JULIAN)       50039L) },
	{ 2038, ((JULIAN)       50404L) },
	{ 2039, ((JULIAN)       50769L) },
	{ 2040, ((JULIAN)       51134L) },
	{ 2041, ((JULIAN)       51500L) },
	{ 2042, ((JULIAN)       51865L) },
	{ 2043, ((JULIAN)       52230L) },
	{ 2044, ((JULIAN)       52595L) },
	{ 2045, ((JULIAN)       52961L) },
	{ 2046, ((JULIAN)       53326L) },
	{ 2047, ((JULIAN)       53691L) },
	{ 2048, ((JULIAN)       54056L) },
	{ 2049, ((JULIAN)       54422L) },
	{ 2050, ((JULIAN)       54787L) },
	{ 2051, ((JULIAN)       55152L) },
	{ 2052, ((JULIAN)       55517L) },
	{ 2053, ((JULIAN)       55883L) },
	{ 2054, ((JULIAN)       56248L) },
	{ 2055, ((JULIAN)       56613L) },
	{ 2056, ((JULIAN)       56978L) },
	{ 2057, ((JULIAN)       57344L) },
	{ 2058, ((JULIAN)       57709L) },
	{ 2059, ((JULIAN)       58074L) },
	{ 2060, ((JULIAN)       58439L) },
	{ 2061, ((JULIAN)       58805L) },
	{ 2062, ((JULIAN)       59170L) },
	{ 2063, ((JULIAN)       59535L) },
	{ 2064, ((JULIAN)       59900L) },
	{ 2065, ((JULIAN)       60266L) },
	{ 2066, ((JULIAN)       60631L) },
	{ 2067, ((JULIAN)       60996L) },
	{ 2068, ((JULIAN)       61361L) },
	{ 2069, ((JULIAN)       61727L) },
	{ 2070, ((JULIAN)       62092L) },
	{ 2071, ((JULIAN)       62457L) },
	{ 2072, ((JULIAN)       62822L) },
	{ 2073, ((JULIAN)       63188L) },
	{ 2074, ((JULIAN)       63553L) },
	{ 2075, ((JULIAN)       63918L) },
	{ 2076, ((JULIAN)       64283L) },
	{ 2077, ((JULIAN)       64649L) },
	{ 2078, ((JULIAN)       65014L) },
	{ 2079, ((JULIAN)       65379L) },
	{ 2080, ((JULIAN)       65744L) },
	{ 2081, ((JULIAN)       66110L) },
	{ 2082, ((JULIAN)       66475L) },
	{ 2083, ((JULIAN)       66840L) },
	{ 2084, ((JULIAN)       67205L) },
	{ 2085, ((JULIAN)       67571L) },
	{ 2086, ((JULIAN)       67936L) },
	{ 2087, ((JULIAN)       68301L) },
	{ 2088, ((JULIAN)       68666L) },
	{ 2089, ((JULIAN)       69032L) },
	{ 2090, ((JULIAN)       69397L) },
	{ 2091, ((JULIAN)       69762L) },
	{ 2092, ((JULIAN)       70127L) },
	{ 2093, ((JULIAN)       70493L) },
	{ 2094, ((JULIAN)       70858L) },
	{ 2095, ((JULIAN)       71223L) },
	{ 2096, ((JULIAN)       71588L) },
	{ 2097, ((JULIAN)       71954L) },
	{ 2098, ((JULIAN)       72319L) },
	{ 2099, ((JULIAN)       72684L) },
	{ 2100, ((JULIAN)       73049L) }
};

static const unsigned int      DATFUNCS_YearMapCount  =
	sizeof(DATFUNCS_YearMapList) / sizeof(DATFUNCS_YearMapList[0]);
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */
static const DATFUNCS_DATE_MAP DATFUNCS_CenturyMapList[] = {
	{  100, ((JULIAN)     -657438L) },
	{  200, ((JULIAN)     -620913L) },
	{  300, ((JULIAN)     -584388L) },
	{  400, ((JULIAN)     -547863L) },
	{  500, ((JULIAN)     -511338L) },
	{  600, ((JULIAN)     -474813L) },
	{  700, ((JULIAN)     -438288L) },
	{  800, ((JULIAN)     -401763L) },
	{  900, ((JULIAN)     -365238L) },
	{ 1000, ((JULIAN)     -328713L) },
	{ 1100, ((JULIAN)     -292188L) },
	{ 1200, ((JULIAN)     -255663L) },
	{ 1300, ((JULIAN)     -219138L) },
	{ 1400, ((JULIAN)     -182613L) },
	{ 1500, ((JULIAN)     -146088L) },
	{ 1600, ((JULIAN)     -109563L) },
	{ 1700, ((JULIAN)      -73038L) },
	{ 1800, ((JULIAN)      -36524L) },
	{ 1900, ((JULIAN)           0L) },
	{ 2000, ((JULIAN)       36524L) },
	{ 2100, ((JULIAN)       73049L) },
	{ 2200, ((JULIAN)      109573L) },
	{ 2300, ((JULIAN)      146097L) },
	{ 2400, ((JULIAN)      182621L) },
	{ 2500, ((JULIAN)      219146L) },
	{ 2600, ((JULIAN)      255670L) },
	{ 2700, ((JULIAN)      292194L) },
	{ 2800, ((JULIAN)      328718L) },
	{ 2900, ((JULIAN)      365243L) },
	{ 3000, ((JULIAN)      401767L) },
	{ 3100, ((JULIAN)      438291L) },
	{ 3200, ((JULIAN)      474815L) },
	{ 3300, ((JULIAN)      511340L) },
	{ 3400, ((JULIAN)      547864L) },
	{ 3500, ((JULIAN)      584388L) },
	{ 3600, ((JULIAN)      620912L) },
	{ 3700, ((JULIAN)      657437L) },
	{ 3800, ((JULIAN)      693961L) },
	{ 3900, ((JULIAN)      730485L) },
	{ 4000, ((JULIAN)      767009L) },
	{ 4100, ((JULIAN)      803534L) },
	{ 4200, ((JULIAN)      840058L) },
	{ 4300, ((JULIAN)      876582L) },
	{ 4400, ((JULIAN)      913106L) },
	{ 4500, ((JULIAN)      949631L) },
	{ 4600, ((JULIAN)      986155L) },
	{ 4700, ((JULIAN)     1022679L) },
	{ 4800, ((JULIAN)     1059203L) },
	{ 4900, ((JULIAN)     1095728L) },
	{ 5000, ((JULIAN)     1132252L) },
	{ 5100, ((JULIAN)     1168776L) },
	{ 5200, ((JULIAN)     1205300L) },
	{ 5300, ((JULIAN)     1241825L) },
	{ 5400, ((JULIAN)     1278349L) },
	{ 5500, ((JULIAN)     1314873L) },
	{ 5600, ((JULIAN)     1351397L) },
	{ 5700, ((JULIAN)     1387922L) },
	{ 5800, ((JULIAN)     1424446L) },
	{ 5900, ((JULIAN)     1460970L) },
	{ 6000, ((JULIAN)     1497494L) },
	{ 6100, ((JULIAN)     1534019L) },
	{ 6200, ((JULIAN)     1570543L) },
	{ 6300, ((JULIAN)     1607067L) },
	{ 6400, ((JULIAN)     1643591L) },
	{ 6500, ((JULIAN)     1680116L) },
	{ 6600, ((JULIAN)     1716640L) },
	{ 6700, ((JULIAN)     1753164L) },
	{ 6800, ((JULIAN)     1789688L) },
	{ 6900, ((JULIAN)     1826213L) },
	{ 7000, ((JULIAN)     1862737L) },
	{ 7100, ((JULIAN)     1899261L) },
	{ 7200, ((JULIAN)     1935785L) },
	{ 7300, ((JULIAN)     1972310L) },
	{ 7400, ((JULIAN)     2008834L) },
	{ 7500, ((JULIAN)     2045358L) },
	{ 7600, ((JULIAN)     2081882L) },
	{ 7700, ((JULIAN)     2118407L) },
	{ 7800, ((JULIAN)     2154931L) },
	{ 7900, ((JULIAN)     2191455L) },
	{ 8000, ((JULIAN)     2227979L) },
	{ 8100, ((JULIAN)     2264504L) },
	{ 8200, ((JULIAN)     2301028L) },
	{ 8300, ((JULIAN)     2337552L) },
	{ 8400, ((JULIAN)     2374076L) },
	{ 8500, ((JULIAN)     2410601L) },
	{ 8600, ((JULIAN)     2447125L) },
	{ 8700, ((JULIAN)     2483649L) },
	{ 8800, ((JULIAN)     2520173L) },
	{ 8900, ((JULIAN)     2556698L) },
	{ 9000, ((JULIAN)     2593222L) },
	{ 9100, ((JULIAN)     2629746L) },
	{ 9200, ((JULIAN)     2666270L) },
	{ 9300, ((JULIAN)     2702795L) },
	{ 9400, ((JULIAN)     2739319L) },
	{ 9500, ((JULIAN)     2775843L) },
	{ 9600, ((JULIAN)     2812367L) },
	{ 9700, ((JULIAN)     2848892L) },
	{ 9800, ((JULIAN)     2885416L) },
	{ 9900, ((JULIAN)     2921940L) }
};

static const unsigned int      DATFUNCS_CenturyMapCount  =
	sizeof(DATFUNCS_CenturyMapList) / sizeof(DATFUNCS_CenturyMapList[0]);
/* *********************************************************************** */

/* *********************************************************************** */
int jultoymd(in_julian, out_year_ptr, out_month_ptr, out_day_ptr)
JULIAN  in_julian;
int    *out_year_ptr;
int    *out_month_ptr;
int    *out_day_ptr;
{
	return(jultoymd_basic(in_julian, out_year_ptr, out_month_ptr, out_day_ptr,
		DATFUNCS_YearMapCount, DATFUNCS_YearMapList));
}
/* *********************************************************************** */

/* *********************************************************************** */
JULIAN ymdtojul(in_year, in_month, in_day)
int in_year;
int in_month;
int in_day;
{
	return(ymdtojul_basic(in_year, in_month, in_day, DATFUNCS_YearMapCount,
		DATFUNCS_YearMapList));
}
/* *********************************************************************** */
              
/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	jultoymd_basic

	SYNOPSIS		:	return_code = jultoymd_basic(in_julian, out_year_ptr,
							out_month_ptr, out_day_ptr);

						int     return_code;

						JULIAN  in_julian;

						int    *out_year_ptr;

						int    *out_month_ptr;

						int    *out_day_ptr;

	DESCRIPTION	:	Converts a ''JULIAN'' date to three integers which
						represent the year, month, and day.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_julian`` is the ''JULIAN'' date to be converted
						by this function into its year, month, and day components.

						(.) ``out_year_ptr`` is a pointer to the ''int'' into which
						this function will place the year component of the
						``in_julian`` date parameter.

						(.) ``out_month_ptr`` is a pointer to the ''int'' into which
						this function will place the month component of the
						``in_julian`` date parameter.

						(.) ``out_day_ptr`` is a pointer to the ''int'' into which
						this function will place the day component of the
						``in_julian`` date parameter.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DATFUNCS_SUCCESS'' if no error occurs.

						(.) One of the non-zero DATFUNCS return codes if an error
						occurs.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	jultoymd
						ymdtojul_basic
						fixed_ymdtojul

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2015 Michael L. Brock

	OUTPUT INDEX:	jultoymd_basic
						Date Functions:Conversion Functions:jultoymd_basic
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	jultoymd_basic

	PUBLISH NAME:	jultoymd_basic

	ENTRY CLASS	:	Date Functions:Conversion Functions

EOH */
/* *********************************************************************** */
int jultoymd_basic(in_julian, out_year_ptr, out_month_ptr, out_day_ptr,
	year_map_count, year_map_list)
JULIAN                   in_julian;
int                     *out_year_ptr;
int                     *out_month_ptr;
int                     *out_day_ptr;
unsigned int             year_map_count;
const DATFUNCS_DATE_MAP *year_map_list;
{
	int                      return_code = DATFUNCS_SUCCESS;
	int                      year_days;
	int                      month_days;
	const DATFUNCS_DATE_MAP *tmp_map_ptr;

	if ((in_julian < DATFUNCS_MIN_JULIAN) ||
		(in_julian > DATFUNCS_MAX_JULIAN)) {
		*out_year_ptr  = 0;
		*out_month_ptr = 0;
		*out_day_ptr   = 0;
		return_code    = DATFUNCS_FAILURE;
	}
	else {
		year_map_count = ((!year_map_count) || (year_map_list == NULL)) ?
			DATFUNCS_YearMapCount : year_map_count;
		year_map_list  = ((!year_map_count) || (year_map_list == NULL)) ?
			DATFUNCS_YearMapList  : year_map_list;
		tmp_map_ptr    = ((in_julian < year_map_list[0].j_year) ||
			(in_julian > year_map_list[year_map_count - 1].j_year)) ?
			DATFUNCS_FIND_DateMap(DATFUNCS_CenturyMapCount,
			DATFUNCS_CenturyMapList, in_julian) :
			DATFUNCS_FIND_DateMap(year_map_count, year_map_list, in_julian);
		*out_year_ptr  = tmp_map_ptr->year;
		*out_month_ptr = 1;
		*out_day_ptr   = 1;
		if (in_julian == tmp_map_ptr->j_year)
			;
		else if (in_julian < ((JULIAN) 0)) {
			in_julian -= tmp_map_ptr->j_year;
/*
			in_julian  = (((JULIAN) 0) - in_julian) - 1;
*/
			while (in_julian >= (year_days = yrdaycnt(*out_year_ptr))) {
				in_julian -= ((JULIAN) year_days);
				(*out_year_ptr)++;
			}
			while (in_julian >= (month_days = mndaycnt(*out_year_ptr,
				*out_month_ptr))) {
				in_julian -= ((JULIAN) month_days);
				(*out_month_ptr)++;
			}
			*out_day_ptr += ((int) in_julian);
			*out_day_ptr += ((*out_year_ptr == DATFUNCS_GREGORIAN_YEAR) &&
				(*out_month_ptr == DATFUNCS_GREGORIAN_MONTH) &&
				(*out_day_ptr >= DATFUNCS_GREGORIAN_FIRST_DAY)) ?
				DATFUNCS_GREGORIAN_MISSING : 0;
/*
	CODE NOTE: To be removed.
			*out_day_ptr = (month_days - ((int) in_julian)) +
				(((*out_year_ptr == DATFUNCS_GREGORIAN_YEAR) &&
				(*out_month_ptr == DATFUNCS_GREGORIAN_MONTH) &&
				((month_days - ((int) in_julian)) >=
				DATFUNCS_GREGORIAN_FIRST_DAY)) ? DATFUNCS_GREGORIAN_MISSING : 0);
*/
		}
		else {
			in_julian -= tmp_map_ptr->j_year;
			while (in_julian >= (year_days = yrdaycnt(*out_year_ptr))) {
				in_julian -= ((JULIAN) year_days);
				(*out_year_ptr)++;
			}
			while (in_julian >= (month_days = mndaycnt(*out_year_ptr,
				*out_month_ptr))) {
				in_julian -= ((JULIAN) month_days);
				(*out_month_ptr)++;
			}
			*out_day_ptr += ((int) in_julian);
/*
	CODE NOTE: To be removed.
			*out_day_ptr = (!in_julian) ? 1 : (((int) in_julian) + 1);
*/
		}
	}

	return(return_code);

#if 0
		if (in_julian < ((JULIAN) 0)) {
			while ((tmp_julian < in_julian) &&
				((0L - tmp_julian) >= (year_days = yrdaycnt(*out_year_ptr)))) {
				tmp_julian += ((JULIAN) year_days);
				(*out_year_ptr)++;
			}
		}
		if (in_julian < ((JULIAN) 0)) {
			*out_year_ptr  = 1899;
			*out_month_ptr = 12;
			*out_day_ptr   = 1;
			in_julian = ((in_julian >= ((JULIAN) 0)) ? in_julian :
				(((JULIAN) 0) - in_julian)) - 1;
			while (in_julian >= (century_days = cndaycnt(*out_year_ptr))) {
				in_julian     -= ((JULIAN) century_days);
				*out_year_ptr -= 100;
			}
			while ((*out_year_ptr > DATFUNCS_MIN_YEAR) &&
				(in_julian >= (year_days = yrdaycnt(*out_year_ptr)))) {
				in_julian -= ((JULIAN) year_days);
				(*out_year_ptr)--;
			}
			while (in_julian >= (month_days = mndaycnt(*out_year_ptr,
				*out_month_ptr))) {
				in_julian -= ((JULIAN) month_days);
				(*out_month_ptr)--;
			}
			*out_day_ptr = (month_days - ((int) in_julian)) +
				(((*out_year_ptr == DATFUNCS_GREGORIAN_YEAR) &&
				(*out_month_ptr == DATFUNCS_GREGORIAN_MONTH) &&
				((month_days - ((int) in_julian)) >=
				DATFUNCS_GREGORIAN_FIRST_DAY)) ? DATFUNCS_GREGORIAN_MISSING : 0);
		}
		else {
			*out_year_ptr  = 1900;
			*out_month_ptr = 1;
			*out_day_ptr   = 1;
			while (in_julian >= (century_days = cndaycnt(*out_year_ptr))) {
				in_julian     -= ((JULIAN) century_days);
				*out_year_ptr += 100;
			}
			while (in_julian >= (year_days = yrdaycnt(*out_year_ptr))) {
				in_julian -= ((JULIAN) year_days);
				(*out_year_ptr)++;
			}
			while (in_julian >= (month_days = mndaycnt(*out_year_ptr,
				*out_month_ptr))) {
				in_julian -= ((JULIAN) month_days);
				(*out_month_ptr)++;
			}
			*out_day_ptr = (!in_julian) ? 1 : (((int) in_julian) + 1);
		}
	}

	return(return_code);
#endif /* #if 0 */

#if 0
/*
	CODE NOTE: Old code --- to be removed.
*/
	if ((in_julian < DATFUNCS_MIN_JULIAN) ||
		(in_julian > DATFUNCS_MAX_JULIAN)) {
		*out_year_ptr  = 0;
		*out_month_ptr = 0;
		*out_day_ptr   = 0;
		return_code    = DATFUNCS_FAILURE;
	}
	else if (in_julian < ((JULIAN) 0)) {
		*out_year_ptr  = 1899;
		*out_month_ptr = 12;
		*out_day_ptr   = 1;
		in_julian = ((in_julian >= ((JULIAN) 0)) ? in_julian :
			(((JULIAN) 0) - in_julian)) - 1;
		while (in_julian >= (century_days = cndaycnt(*out_year_ptr))) {
			in_julian     -= ((JULIAN) century_days);
			*out_year_ptr -= 100;
		}
		while ((*out_year_ptr > DATFUNCS_MIN_YEAR) &&
			(in_julian >= (year_days = yrdaycnt(*out_year_ptr)))) {
			in_julian -= ((JULIAN) year_days);
			(*out_year_ptr)--;
		}
		while (in_julian >= (month_days = mndaycnt(*out_year_ptr,
			*out_month_ptr))) {
			in_julian -= ((JULIAN) month_days);
			(*out_month_ptr)--;
		}
		*out_day_ptr = (month_days - ((int) in_julian)) +
			(((*out_year_ptr == DATFUNCS_GREGORIAN_YEAR) &&
			(*out_month_ptr == DATFUNCS_GREGORIAN_MONTH) &&
			((month_days - ((int) in_julian)) >=
			DATFUNCS_GREGORIAN_FIRST_DAY)) ? DATFUNCS_GREGORIAN_MISSING : 0);
	}
	else {
		*out_year_ptr  = 1900;
		*out_month_ptr = 1;
		*out_day_ptr   = 1;
		while (in_julian >= (century_days = cndaycnt(*out_year_ptr))) {
			in_julian     -= ((JULIAN) century_days);
			*out_year_ptr += 100;
		}
		while (in_julian >= (year_days = yrdaycnt(*out_year_ptr))) {
			in_julian -= ((JULIAN) year_days);
			(*out_year_ptr)++;
		}
		while (in_julian >= (month_days = mndaycnt(*out_year_ptr,
			*out_month_ptr))) {
			in_julian -= ((JULIAN) month_days);
			(*out_month_ptr)++;
		}
		*out_day_ptr = (!in_julian) ? 1 : (((int) in_julian) + 1);
	}

	return(return_code);
#endif /* #if 0 */
}
/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	ymdtojul_basic

	SYNOPSIS		:	julian_date = ymdtojul_basic(in_year, in_month, in_day);

						JULIAN julian_date;

						int    in_year;

						int    in_month;

						int    in_day;

	DESCRIPTION	:	Converts three integers representing year, month, and
						day to a ''JULIAN'' date.

						(.) ``in_year`` is the year to be converted by this
						function.

						(.) ``in_month`` is the month to be converted by this
						function.

						(.) ``in_day`` is the day to be converted by this function.

	PARAMETERS  :  Parameters to this function are as follow:

   RETURNS     :  Returns the ''JULIAN'' equivalent of the date represented
						by the ``in_year``, ``in_month``, and ``in_day`` parameters.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	ymdtojul
						jultoymd_basic
						fixed_ymdtojul

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2015 Michael L. Brock

	OUTPUT INDEX:	ymdtojul_basic
						Date Functions:Conversion Functions:ymdtojul_basic
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	ymdtojul_basic

	PUBLISH NAME:	ymdtojul_basic

	ENTRY CLASS	:	Date Functions:Conversion Functions

EOH */
/* *********************************************************************** */
JULIAN ymdtojul_basic(in_year, in_month, in_day, year_map_count, year_map_list)
int                      in_year;
int                      in_month;
int                      in_day;
unsigned int             year_map_count;
const DATFUNCS_DATE_MAP *year_map_list;
{
	int    tmp_month  = 1;
	int    tmp_year;
	JULIAN tmp_julian;

	if (ymdok(in_year, in_month, in_day) == DATFUNCS_TRUE) {
		year_map_count    = ((!year_map_count) || (year_map_list == NULL)) ?
			DATFUNCS_YearMapCount : year_map_count;
		year_map_list     = ((!year_map_count) || (year_map_list == NULL)) ?
			DATFUNCS_YearMapList  : year_map_list;
		if ((in_year < year_map_list[0].year) ||
			(in_year > year_map_list[year_map_count - 1].year)) {
			tmp_julian =
				DATFUNCS_CenturyMapList[(in_year - DATFUNCS_MIN_YEAR) / 100].j_year;
			tmp_year   = 
				DATFUNCS_CenturyMapList[(in_year - DATFUNCS_MIN_YEAR) / 100].year;
		}
		else {
			tmp_julian = year_map_list[in_year - year_map_list[0].year].j_year;
			tmp_year   = year_map_list[in_year - year_map_list[0].year].year;
		}
#if 0
/*
	CODE NOTE: To be removed.
*/
		while (((tmp_year - 100) >= DATFUNCS_MIN_YEAR) &&
			(in_year <= (tmp_year - 100))) {
			tmp_julian -= ((JULIAN) cndaycnt(tmp_year - 100));
			tmp_year   -= 100;
		}
		while (((tmp_year + 100) <= DATFUNCS_MAX_YEAR) &&
			(in_year >= (tmp_year + 100))) {
			tmp_julian += ((JULIAN) cndaycnt(tmp_year));
			tmp_year   += 100;
		}
#endif /* #if 0 */
#if 0
/*
	CODE NOTE: To be removed.
*/
		while (in_year < tmp_year)
			tmp_julian -= ((JULIAN) yrdaycnt(--tmp_year));
#endif /* #if 0 */
		while (in_year > tmp_year)
			tmp_julian += ((JULIAN) yrdaycnt(tmp_year++));
		while (in_month > tmp_month)
			tmp_julian += ((JULIAN) mndaycnt(tmp_year, tmp_month++));
		tmp_julian += ((JULIAN) ((((tmp_year == DATFUNCS_GREGORIAN_YEAR) &&
			(tmp_month == DATFUNCS_GREGORIAN_MONTH) &&
			(in_day > DATFUNCS_GREGORIAN_LAST_DAY)) ?
			(in_day - DATFUNCS_GREGORIAN_MISSING) : in_day) - 1));
	}

	return(tmp_julian);
}
/*	*********************************************************************** */

/* *********************************************************************** */
int DATFUNCS_CreateDateMap(first_year, last_year, century_flag,
	date_map_count, date_map_list, error_text)
unsigned int        first_year;
unsigned int        last_year;
int                 century_flag;
unsigned int       *date_map_count;
DATFUNCS_DATE_MAP **date_map_list;
char               *error_text;
{
	int          return_code = DATFUNCS_SUCCESS;
	unsigned int increment_count;
	unsigned int element_count;

	*date_map_count = 0;
	*date_map_list  = NULL;

	increment_count = (century_flag) ? 100 : 1;
	element_count   = ((last_year - first_year) / increment_count) + 1;

	if (first_year < DATFUNCS_MIN_YEAR) {
		sprintf(error_text, "%s ('%u') %s.",
			"Invalid first year value", first_year,
			"passed to date map creation function");
		return_code = DATFUNCS_FAILURE;
	}
	else if (last_year > DATFUNCS_MAX_YEAR) {
		sprintf(error_text, "%s ('%u') %s.",
			"Invalid lasst year value", last_year,
			"passed to date map creation function");
		return_code = DATFUNCS_FAILURE;
	}
	else if (first_year > last_year) {
		sprintf(error_text, "%s ('%u') is greater than the last year ('%u').",
			"The first year passed to the dat map creation function", first_year,
			last_year);
		return_code = DATFUNCS_FAILURE;
   }
	else if ((*date_map_list = ((DATFUNCS_DATE_MAP *)
		calloc(element_count, sizeof(DATFUNCS_DATE_MAP)))) == NULL) {
		STR_AllocMsgList(element_count, sizeof(DATFUNCS_DATE_MAP), error_text,
			"Unable to allocate the date map array");
		return_code = DATFUNCS_MEMORY_FAILURE;
   }
   else {
   	for ( ; first_year <= last_year; first_year += increment_count) {
      	(*date_map_list)[*date_map_count].year            = first_year;
         (*date_map_list)[(*date_map_count)++].j_year =
				ymdtojul(first_year, 1, 1);
		}
if (element_count != *date_map_count) {
	sprintf(error_text,
		"ERROR: 'element_count' = '%u' --- '*date_map_count' = '%u'.",
		element_count, *date_map_count);
	return_code = DATFUNCS_FAILURE;
}
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
static const DATFUNCS_DATE_MAP *DATFUNCS_FIND_DateMap(date_map_count,
	date_map_list, in_julian)
unsigned int             date_map_count;
const DATFUNCS_DATE_MAP *date_map_list;
JULIAN                   in_julian;
{
	DATFUNCS_DATE_MAP tmp_map;
	unsigned int      found_index;

	tmp_map.j_year = in_julian;

#ifndef NARGS
	if ((STR_ARRAY_bsearch(NULL, date_map_count, date_map_list, &tmp_map,
		sizeof(date_map_list[0]), &found_index, STRFUNCS_DIRECTION_TOP,
		((int (*)(void *, const void *, const void *, size_t))
		DATFUNCS_CMP_DateMap)) == STRFUNCS_ITEM_NOT_FOUND) && found_index)
#else
	if ((STR_ARRAY_bsearch(NULL, date_map_count, date_map_list, &tmp_map,
		sizeof(date_map_list[0]), &found_index, STRFUNCS_DIRECTION_TOP,
		DATFUNCS_CMP_DateMap) == STRFUNCS_ITEM_NOT_FOUND) && found_index)
#endif /* #ifndef NARGS */
		found_index--;

	return(date_map_list + found_index);
}
/* *********************************************************************** */

/* *********************************************************************** */
static int DATFUNCS_CMP_DateMap(control_ptr, ptr_1, ptr_2, data_length)
void                    *control_ptr;
const DATFUNCS_DATE_MAP *ptr_1;
const DATFUNCS_DATE_MAP *ptr_2;
size_t                   data_length;
{
	return((ptr_1->j_year > ptr_2->j_year) ? 1 :
		(ptr_1->j_year < ptr_2->j_year) ? -1 : 0);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

#ifndef NARGS
int    main(int, char **);
static int    DoCreate(void);
static void   DoCreateEmit(unsigned int date_map_count,
	const DATFUNCS_DATE_MAP *date_map_list, const char *name_tag);
static int    OLD_jultoymd(JULIAN in_julian, int *out_year_ptr, int *out_month_ptr,
	int *out_day_ptr);
static JULIAN OLD_ymdtojul(int in_year, int in_month, int in_day);
#else
int    main();
static int    DoCreate();
static void   DoCreateEmit();
static int    OLD_jultoymd();
static JULIAN OLD_ymdtojul();
#endif /* #ifndef NARGS */

/*	*********************************************************************** */
/*	*********************************************************************** */
/*	*********************************************************************** */
int main(argc, argv)
int    argc;
char **argv;
{
	int            return_code   = DATFUNCS_SUCCESS;
	int            first_year    = DATFUNCS_MIN_YEAR;
	int            last_year     = DATFUNCS_MAX_YEAR;
	int            first_month   = 1;
	int            last_month    = 12;
	int            first_day     = 1;
	unsigned int   failure_count = 0;
	int            print_flag    = DATFUNCS_FALSE;
	int            create_flag   = DATFUNCS_FALSE;
	unsigned long  century_days  = 0L;
	unsigned long  total_days    = 0L;
	double         century_time  = 0.0;
	double         total_time    = 0.0;
	JULIAN         previous_year;
	JULIAN         tmp_julian;
	JDATE          tmp_jdate;
	JULIAN         old_julian;
	JDATE          old_jdate;
	int            count_1;
	int            count_2;
	int            count_3;
	struct timeval start_time;
	struct timeval end_time;

	fprintf(stderr, "Test routine for function 'datemaps()'\n");
	fprintf(stderr, "---- ------- --- -------- ------------\n\n");

	for (count_1 = 1; count_1 < argc; count_1++) {
		if (!stricmp(argv[count_1], "-PRINT"))
			print_flag = DATFUNCS_TRUE;
		else if (!stricmp(argv[count_1], "-CREATE"))
			create_flag = DATFUNCS_TRUE;
	}

	if (create_flag == DATFUNCS_TRUE) {
		DoCreate();
		goto EXIT_FUNCTION;
	}

	fprintf(stderr, "Minimum Julian Date: %11ld (%4d-01-01)\n",
		ymdtojul(first_year, 1, 1), first_year);
	fprintf(stderr, "Maximum Julian Date: %11ld (%4d-12-31)\n",
		ymdtojul(last_year, 12, 31), last_year);
	fprintf(stderr, "\n");

	previous_year = first_year;

	fprintf(stderr, "%s\n",
		"=== ===== ==== == ==== == =========== = =========== === ===");

	SDTIF_GetTimeUSecs(&start_time);

/*
first_year  = DATFUNCS_GREGORIAN_YEAR;
last_year   = DATFUNCS_GREGORIAN_YEAR;
first_month = DATFUNCS_GREGORIAN_MONTH;
last_month  = DATFUNCS_GREGORIAN_MONTH;
first_day   = DATFUNCS_GREGORIAN_FIRST_DAY - 1;
*/
/*
first_year  = 1899;
last_year   = 1900;
first_month = 1;
last_month  = 12;
first_day   = 1;
*/
	for (count_1 = first_year; count_1 <= last_year; count_1++) {
		for (count_2 = first_month; count_2 <= last_month; count_2++) {
			for (count_3 = first_day; count_3 <= mndaymax(count_1, count_2);
				count_3++) {
				if ((count_1 == DATFUNCS_GREGORIAN_YEAR) &&
					(count_2 == DATFUNCS_GREGORIAN_MONTH) &&
					(count_3 >= DATFUNCS_GREGORIAN_FIRST_DAY) &&
					(count_3 <= DATFUNCS_GREGORIAN_LAST_DAY))
					continue;
				century_days++;
				jultoymd(tmp_julian = ymdtojul(count_1, count_2, count_3),
					&tmp_jdate.year, &tmp_jdate.month, &tmp_jdate.day);
				if ((count_1 != tmp_jdate.year) || (count_2 != tmp_jdate.month) ||
					(count_3 != tmp_jdate.day)) {
					printf(
"Date %04d-%02d-%02d --- julian = %11ld --- FAILED (returned %04d-%02d-%02d)\n",
						count_1, count_2, count_3, tmp_julian,
						tmp_jdate.year, tmp_jdate.month, tmp_jdate.day);
					failure_count++;
					return_code = DATFUNCS_FAILURE;
				}
				else if (print_flag == DATFUNCS_TRUE)
					printf("Date %04d-%02d-%02d --- julian = %11ld\n",
						count_1, count_2, count_3, tmp_julian);
#if 0
				old_julian = OLD_ymdtojul(count_1, count_2, count_3);
				OLD_jultoymd(old_julian, &old_jdate.year, &old_jdate.month,
					&old_jdate.day);
				if ((old_julian != tmp_julian) || (count_1 != old_jdate.year) ||
					(count_2 != old_jdate.month) || (count_3 != old_jdate.day)) {
					printf("*** REGRESSION TEST FAILURE ***\n");
					printf("OLD: Date %04d-%02d-%02d --- julian = %11ld\n",
						old_jdate.year, old_jdate.month, old_jdate.day,
						old_julian);
					printf("NEW: Date %04d-%02d-%02d --- julian = %11ld\n",
						tmp_jdate.year, tmp_jdate.month, tmp_jdate.day,
						tmp_julian);
				}
#endif /* #if 0 */
			}
		}
		if ((((count_1 / 100) * 100) == count_1) &&
			(previous_year != count_1)) {
			SDTIF_GetTimeUSecs(&end_time);
			end_time.tv_sec   -= start_time.tv_sec;
			start_time.tv_sec  = 0L;
			century_time       = (((double) SDTIF_GET_TIMEVAL_USECS(&end_time)) -
				((double) SDTIF_GET_TIMEVAL_USECS(&start_time))) / 1000000.0;
			total_days        += century_days;
			total_time        += century_time;
			fprintf(stderr,
				"Did years %4ld to %4d in %11.6f / %11.6f per day\n",
				previous_year, count_1, century_time,
				century_time / ((double) century_days));
			previous_year = count_1 + 1;
			century_days  = 0;
			SDTIF_GetTimeUSecs(&start_time);
		}
	}

	if ((((count_1 / 100) * 100) != count_1) &&
		(previous_year != count_1)) {
		SDTIF_GetTimeUSecs(&end_time);
		end_time.tv_sec   -= start_time.tv_sec;
		start_time.tv_sec  = 0L;
		century_time       = (((double) SDTIF_GET_TIMEVAL_USECS(&end_time)) -
			((double) SDTIF_GET_TIMEVAL_USECS(&start_time))) / 1000000.0;
		total_days        += century_days;
		total_time        += century_time;
		fprintf(stderr,
			"Did years %4d to %4d in %11.6f / %11.6f per day\n",
			previous_year, count_1, century_time,
			century_time / ((double) century_days));
	}

	fprintf(stderr, "%s\n",
		"--- ----- ---- -- ---- -- ----------- - ----------- --- ---");
	fprintf(stderr,
		"Did years %4d to %4d in %11.6f / %11.6f per day\n",
		first_year, last_year, total_time, total_time / ((double) total_days));
	fprintf(stderr, "%s\n",
		"=== ===== ==== == ==== == =========== = =========== === ===");

EXIT_FUNCTION:

	if (return_code != DATFUNCS_SUCCESS)
		fprintf(stderr, "Test FAILED (%u failures).\n", failure_count);
	else
		fprintf(stderr, "Test SUCCEEDED.\n");

	return(return_code);
}
/*	*********************************************************************** */

/*	*********************************************************************** */
static int DoCreate()
{
	int                return_code;
	unsigned int       date_map_count;
	DATFUNCS_DATE_MAP *date_map_list;
   char               error_text[DATFUNCS_MAX_ERROR_TEXT];

   if ((return_code = DATFUNCS_CreateDateMap(1800, 2100, DATFUNCS_FALSE,
   	&date_map_count, &date_map_list, error_text)) == DATFUNCS_SUCCESS) {
      DoCreateEmit(date_map_count, date_map_list, "YearMap");
      mema_remove_all(&date_map_count, ((void **) &date_map_list));
	   if ((return_code = DATFUNCS_CreateDateMap(DATFUNCS_MIN_YEAR,
      	DATFUNCS_MAX_YEAR, DATFUNCS_TRUE, &date_map_count, &date_map_list,
         error_text)) == DATFUNCS_SUCCESS) {
      	DoCreateEmit(date_map_count, date_map_list, "CenturyMap");
	      mema_remove_all(&date_map_count, ((void **) &date_map_list));
      }
   }

	return(return_code);
}
/*	*********************************************************************** */

/*	*********************************************************************** */
static void DoCreateEmit(date_map_count, date_map_list, name_tag)
unsigned int             date_map_count;
const DATFUNCS_DATE_MAP *date_map_list;
const char              *name_tag;
{
	printf("static const DATFUNCS_DATE_MAP DATFUNCS_%sList[] = {\n",
   	name_tag);
   while (date_map_count) {
   	printf("\t{ %4u, ((JULIAN) %11ldL) }%s\n",
			date_map_list->year, ((long) date_map_list->j_year),
         (date_map_count == 1) ? "" : ",");
      date_map_count--;
      date_map_list++;
   }
   printf("};\n\n");
   printf("static const unsigned int      DATFUNCS_%sCount  =\n", name_tag);
   printf("\tsizeof(DATFUNCS_%sList) / sizeof(DATFUNCS_%sList[0]);\n\n",
		name_tag, name_tag);
}
/*	*********************************************************************** */

/*	*********************************************************************** */
static int OLD_jultoymd(in_julian, out_year_ptr, out_month_ptr, out_day_ptr)
JULIAN  in_julian;
int    *out_year_ptr;
int    *out_month_ptr;
int    *out_day_ptr;
{
	int  return_code = DATFUNCS_SUCCESS;
	long century_days;
	int  year_days;
	int  month_days;

	if ((in_julian < DATFUNCS_MIN_JULIAN) ||
		(in_julian > DATFUNCS_MAX_JULIAN)) {
		*out_year_ptr  = 0;
		*out_month_ptr = 0;
		*out_day_ptr   = 0;
		return_code    = DATFUNCS_FAILURE;
	}
	else if (in_julian < ((JULIAN) 0)) {
		*out_year_ptr  = 1899;
		*out_month_ptr = 12;
		*out_day_ptr   = 1;
		in_julian = ((in_julian >= ((JULIAN) 0)) ? in_julian :
			(((JULIAN) 0) - in_julian)) - 1;
		while (in_julian >= (century_days = cndaycnt(*out_year_ptr))) {
			in_julian     -= ((JULIAN) century_days);
			*out_year_ptr -= 100;
		}
		while ((*out_year_ptr > DATFUNCS_MIN_YEAR) &&
			(in_julian >= (year_days = yrdaycnt(*out_year_ptr)))) {
			in_julian -= ((JULIAN) year_days);
			(*out_year_ptr)--;
		}
		while (in_julian >= (month_days = mndaycnt(*out_year_ptr,
			*out_month_ptr))) {
			in_julian -= ((JULIAN) month_days);
			(*out_month_ptr)--;
		}
		*out_day_ptr = (month_days - ((int) in_julian)) +
			(((*out_year_ptr == DATFUNCS_GREGORIAN_YEAR) &&
			(*out_month_ptr == DATFUNCS_GREGORIAN_MONTH) &&
			((month_days - ((int) in_julian)) >=
			DATFUNCS_GREGORIAN_FIRST_DAY)) ? DATFUNCS_GREGORIAN_MISSING : 0);
	}
	else {
		*out_year_ptr  = 1900;
		*out_month_ptr = 1;
		*out_day_ptr   = 1;
		while (in_julian >= (century_days = cndaycnt(*out_year_ptr))) {
			in_julian     -= ((JULIAN) century_days);
			*out_year_ptr += 100;
		}
		while (in_julian >= (year_days = yrdaycnt(*out_year_ptr))) {
			in_julian -= ((JULIAN) year_days);
			(*out_year_ptr)++;
		}
		while (in_julian >= (month_days = mndaycnt(*out_year_ptr,
			*out_month_ptr))) {
			in_julian -= ((JULIAN) month_days);
			(*out_month_ptr)++;
		}
		*out_day_ptr = (!in_julian) ? 1 : (((int) in_julian) + 1);
	}

	return(return_code);
}
/*	*********************************************************************** */

/*	*********************************************************************** */
static JULIAN OLD_ymdtojul(in_year, in_month, in_day)
int in_year;
int in_month;
int in_day;
{
	JULIAN tmp_julian = ((JULIAN) 0);
	int    tmp_year   = 1900;
	int    tmp_month  = 1;

	if (ymdok(in_year, in_month, in_day) == DATFUNCS_TRUE) {
		while (((tmp_year - 100) >= DATFUNCS_MIN_YEAR) &&
			(in_year <= (tmp_year - 100))) {
			tmp_julian -= ((JULIAN) cndaycnt(tmp_year - 100));
			tmp_year   -= 100;
		}
		while (((tmp_year + 100) <= DATFUNCS_MAX_YEAR) &&
			(in_year >= (tmp_year + 100))) {
			tmp_julian += ((JULIAN) cndaycnt(tmp_year));
			tmp_year   += 100;
		}
		while (in_year < tmp_year)
			tmp_julian -= ((JULIAN) yrdaycnt(--tmp_year));
		while (in_year > tmp_year)
			tmp_julian += ((JULIAN) yrdaycnt(tmp_year++));
		while (in_month > tmp_month)
			tmp_julian += ((JULIAN) mndaycnt(tmp_year, tmp_month++));
		tmp_julian += ((JULIAN) ((((tmp_year == DATFUNCS_GREGORIAN_YEAR) &&
			(tmp_month == DATFUNCS_GREGORIAN_MONTH) &&
			(in_day > DATFUNCS_GREGORIAN_LAST_DAY)) ?
			(in_day - DATFUNCS_GREGORIAN_MISSING) : in_day) - 1));
	}

	return(tmp_julian);
}
/*	*********************************************************************** */

#endif /* #ifdef TEST_MAIN */

