#ifndef RESULTS_HEADER
#define RESULTS_HEADER

namespace Results{
    enum class Database{
        Ok,
        ConstraintViolated,
        PrimaryKeyViolated,
        UniqueKeyViolated,
    };
};
#endif