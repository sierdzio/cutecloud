set(VERSION 0.0.1)
set(APP_NAME "Cutecloud")
set(COMPANY_NAME "none")
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
  AppName="${APP_NAME}"
  AppVersion="${VERSION}"
  CompanyName="${COMPANY_NAME}"
  CompanyDomain="${COMPANY_DOMAIN}"
  BuildDate="${BUILD_DATE}"
  GitCommit="${SHORT_HASH}"
  )

message(
  "  App name: " ${APP_NAME} "\n"
  "  Version: " ${VERSION} "\n"
  "  Company: " ${COMPANY_NAME} "\n"
  "  Domain: " ${COMPANY_DOMAIN} "\n"
  "  Build date: " ${BUILD_DATE} "\n"
  "  Git SHA: " ${SHORT_HASH}
  )
