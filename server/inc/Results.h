#ifndef RESULTS_HEADER
#define RESULTS_HEADER

/*! A namespace containing results of other functions, for example database operations.*/
namespace Results{
    /*! Enum class, results of database operations.*/
    enum class Database{
        Ok, /*!< Operation successfull.*/
        ConstraintViolated,/*!< Operation would have violated a constraint. Use a more specific Result if available.*/
        PrimaryKeyViolated,/*!< Operation would have violated a primary key constraint.*/
        UniqueViolated,/*!< Operation would have violated an unique constraint.*/
        NotFound,/*!< Entity was not in the database.*/
        DatabaseUnavailable/*!< Connection to the database was not estabilished.*/
    };
};
#endif