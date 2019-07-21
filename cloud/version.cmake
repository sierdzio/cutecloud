set(CLOUD_VERSION 0.0.1)
set(CLOUD_APP_NAME "cutecloud")
set(COMPANY_NAME "Cutecloud")
set(COMPANY_DOMAIN "sierdzio.com")
string(TIMESTAMP BUILD_DATE "%Y-%m-%d" UTC)

find_package(Git QUIET REQUIRED)

execute_process(
  COMMAND "${GIT_EXECUTABLE}"  rev-parse --short HEAD
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  RESULT_VARIABLE SHORT_HASH_RESULT
  OUTPUT_VARIABLE SHORT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
  )

set_property(GLOBAL APPEND
  PROPERTY CMAKE_CONFIGURE_DEPENDS
  "${CMAKE_SOURCE_DIR}/.git/index")

add_compile_definitions(
  CloudAppName="${CLOUD_APP_NAME}"
  CloudAppVersion="${CLOUD_VERSION}"
  CompanyName="${COMPANY_NAME}"
  CompanyDomain="${COMPANY_DOMAIN}"
  BuildDate="${BUILD_DATE}"
  GitCommit="${SHORT_HASH}"
  )

message(
  "  Cloud app name: " ${CLOUD_APP_NAME} "\n"
  "  Cloud version: " ${CLOUD_VERSION} "\n"
  "  Company: " ${COMPANY_NAME} "\n"
  "  Domain: " ${COMPANY_DOMAIN} "\n"
  "  Build date: " ${BUILD_DATE} "\n"
  "  Git SHA: " ${SHORT_HASH}
  )
