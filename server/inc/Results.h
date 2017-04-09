#ifndef RESULTS_HEADER
#define RESULTS_HEADER

namespace Results{
    enum class Database{
        Ok,
        ConstraintViolated,
        PrimaryKeyViolated,
        UniqueViolated,
        NotFound,
        DatabaseUnavailable
    };
};
#endif