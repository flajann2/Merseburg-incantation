# set headers
set(header_path "${MERSEBERG_SOURCE_DIR}/include")
set(header ${header_path}/header/merseberg
	${header_path}/merseberg/merseberg.h)

# configure config.h.in
configure_file("config.h.in" "${CMAKE_CURRENT_BINARY_DIR}/config_impl.h")

# define library target
add_library(merseberg INTERFACE)
target_include_directories(merseberg INTERFACE ${MERSEBERG_SOURCE_DIR}/include)
			
