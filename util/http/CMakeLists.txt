add_library(http_beast_prebuilt prebuilt_beast.cc)

add_library(http_common http_common.cc status_page.cc profilez_handler.cc)
cxx_link(http_common absl_strings base http_beast_prebuilt proc_stats stats_lib fast_malloc)

add_library(http_v2  http_conn_handler.cc )
cxx_link(http_v2 asio_fiber_lib strings stats_lib http_common)

add_executable(http_main http_main.cc)
cxx_link(http_main http_v2 html_lib)

add_library(http_client_lib http_client.cc)
cxx_link(http_client_lib strings asio_fiber_lib)

add_library(https_client_lib https_client.cc https_client_pool.cc ssl_stream.cc)
cxx_link(https_client_lib strings asio_fiber_lib absl_variant http_beast_prebuilt ssl crypto)
cxx_test(ssl_stream_test https_client_lib LABELS CI)


add_library(http_test_lib http_testing.cc)
cxx_link(http_test_lib http_v2 gaia_gtest_main TRDP::rapidjson)

cxx_test(http_test http_v2 http_client_lib http_test_lib LABELS CI)
