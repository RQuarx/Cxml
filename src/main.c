#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cJSON.h>

#include "objects/map.h"
#include "print.h"
#include "utils.h"

#define IS_ARG( p_str, p_short, p_long )             \
    strncmp(p_str, p_short, strlen(p_short)) == 0 || \
    strncmp(p_str, p_long, strlen(p_long))   == 0


[[noreturn]]
static void
print_usage( void )
{
    println("Usage: %s <options> <files>\n", APP_NAME);
    println("Options:");
    println("  -j --json          Output compiled data as JSON. (unformatted)");
    println("  -V --version       Print the version information.");
    println("  -h --help          Print the app's usage message.");
    exit(0);
}


[[noreturn]]
static void
print_version( void )
{
    println("%s %s", APP_NAME, APP_VERSION);

    for (size_t i = 0; i <= strlen(APP_NAME) + strlen(APP_VERSION) ; i++)
        putchar('-');

    println("\n  cjson %d.%d.%d", CJSON_VERSION_MAJOR,
                                 CJSON_VERSION_MINOR,
                                 CJSON_VERSION_PATCH);
    exit(0);
}


[[gnu::nonnull(1)]]
static bool
check_path_exist_and_is_file( const char *restrict p_path )
{
    struct stat s;
    return stat(p_path, &s) == 0
        && S_ISREG(s.st_mode);
}


int
main( int32_t argc, char **argv )
{
    // if (argc == 1) print_usage();

    // int32_t files_index = 1;
    // bool    output_json = false;

    // for (; files_index < argc; files_index++) {
    //     const char *arg = argv[files_index];
    //     if (arg[0] != '-') break;

    //     if (IS_ARG(arg, "-h", "--help"))
    //         print_usage();

    //     if (IS_ARG(arg, "-V", "--version"))
    //         print_version();

    //     if (IS_ARG(arg, "-j", "--json"))
    //         output_json = true;
    // }

    // if (output_json) println_dbg("Running with JSON data.");
    // /* After the for loop, `files_index` would point to the start of
    //    the list of files passed by the user.
    // */

    // /* Ensure that the parsing time will not be
    //    wasted if an invalid file is found.
    // */
    // for (int32_t i = files_index; i < argc; i++)
    //     if (!check_path_exist_and_is_file(argv[i]))
    //         ERR("File '%s' does not exist", argv[i]);

    // for (int32_t i = files_index; i < argc; i++) {
    //     int32_t fd = open(argv[i], O_RDONLY);
    //     if (fd < 0)
    //         ERR("Failed to open file '%s': %s", argv[i], strerror(errno));

    //     int64_t len = lseek(fd, 0, SEEK_END);
    //     if (len < 0)
    //         ERR("Failed to seek to the end of file '%s': %s",
    //              argv[i], strerror(errno));

    //     void *file = mmap(0, len, PROT_READ, MAP_PRIVATE, fd, 0);
    //     if (file == MAP_FAILED)
    //         ERR("mmap failed: %s", strerror(errno));
    // }
    struct map *map = map_new(5);
    map_add(map, "key", "value");
    map_add(map, "test", "value2");
    println("%s: %s", map_get(map, "key"), map_get(map, "test"));

}
