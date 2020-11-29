#define print_fatal_error(x)             \
  fprintf(stderr,                        \
          "%s:%d: "                      \
          "\033[1;31m"                   \
          "fatal error"                  \
          "\033[0m"                      \
          ": In function '%s', " x "\n", \
          __FILE__, __LINE__, __func__)
#define print_only_error(x)              \
  fprintf(stderr,                        \
          "%s:%d: "                      \
          "\033[1;31m"                   \
          "error"                        \
          "\033[0m"                      \
          ": In function '%s', " x "\n", \
          __FILE__, __LINE__, __func__)
#define print_logical_error(x)           \
  fprintf(stderr,                        \
          "%s:%d: "                      \
          "\033[1;31m"                   \
          "logical error"                \
          "\033[0m"                      \
          ": In function '%s', " x "\n", \
          __FILE__, __LINE__, __func__)
#define print_error_continue(x) fprintf(stderr, x)
#define construct_list_error(x)                                           \
  ({                                                                      \
    print_fatal_error("list is not constructed...");                      \
    print_error_continue(x "\n");                                         \
    print_error_continue(                                                 \
        "first try constructing it using following function...\n");       \
    print_error_continue(                                                 \
        "list* construct(list *this_list, void (*compare)(const void *, " \
        "const void *), void (*print)(const void *))\n");                 \
  })
