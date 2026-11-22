
set(XC8_TARGET "test123_default_default_XC8_compile")

# Путь к общей папке проекта
get_filename_component(USER_ROOT
    "${CMAKE_CURRENT_LIST_DIR}/../../../default"
    ABSOLUTE
)

# Проверяем путь
if(NOT EXISTS "${USER_ROOT}/include/main.h")
    message(FATAL_ERROR
        "USER DEBUG: main.h not found in ${USER_ROOT}/include"
    )
endif()

# Подключаем заголовки
target_include_directories("${XC8_TARGET}" PRIVATE
    "${USER_ROOT}/include"
    "${USER_ROOT}/src"
)

# Диагностика
get_target_property(DIRS "${XC8_TARGET}" INCLUDE_DIRECTORIES)

message(STATUS "")
message(STATUS "############################################################")
message(STATUS "################## USER DEBUG START ########################")
message(STATUS "  USER ROOT: ${USER_ROOT}")
message(STATUS "  INCLUDE DIRS: ${DIRS}")
message(STATUS "################### USER DEBUG END #########################")
message(STATUS "############################################################")
message(STATUS "")
