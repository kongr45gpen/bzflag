TESTS = tests
check_PROGRAMS = $(TESTS)

AM_CPPFLAGS = -DINSIDE_BZ \
	-DINSTALL_DATA_DIR=\"$(pkgdatadir)\" \
	$(LIBCURL_CPPFLAGS) \
	$(CONF_CPPFLAGS) \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/src/bzflag \
	-I$(top_srcdir)/src/bzfs
AM_CFLAGS = $(CONF_CFLAGS)
AM_CXXFLAGS = $(CONF_CXXFLAGS)

tests_SOURCES = bans.cxx tests.cxx
tests_CXXFLAGS = -I/usr/include/CppUTest/include -L/usr/include/CppUTest/lib -lCppUTest
tests_LDFLAGS = -L/usr/include/CppUTest/lib -lCppUTest

LDADD =					\
	../src/obstacle/libObstacle.la	\
	../src/game/libGame.la		\
	../src/net/libNet.la		\
	../src/common/libCommon.la	\
	$(LIBCURL)			\
	$(LIBCARES)			\
	$(LIBREGEX)			\
	$(LIBZ)				\
	$(LIBDL)			\
	$(LIBMINIUPNPC)			\
	../src/date/libDate.la
