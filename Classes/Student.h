#ifndef AED_PROJECT_STUDENT_H
#define AED_PROJECT_STUDENT_H

#include <string>
#include <vector>
#include "Schedule.h"

/**
 * @class Student
 * @brief Classe que representa um estudante com informações sobre o seu código, nome e horário.
 */
class Student {
public:
    /**
     * @brief Construtor que inicializa um objeto Student com código, nome e horário.
     * @param StudentCode_ Código do estudante.
     * @param StudentName_ Nome do estudante.
     * @param horario Horário do estudante (objeto Schedule).
     */
    Student(std::string StudentCode_, std::string StudentName_, Schedule horario);

    /**
     * @brief Construtor que inicializa um objeto Student com código e nome.
     * @param StudentCode_ Código do estudante.
     * @param StudentName_ Nome do estudante.
     */
    Student(std::string StudentCode_, std::string StudentName_);

    /**
     * @brief Construtor padrão que inicializa um objeto Student sem informações.
     */
    Student();

    /**
     * @brief Destrutor da classe Student.
     */
    ~Student();

    // Operadores

    /**
     * @brief Sobrecarga do operador de igualdade para comparar dois objetos Student.
     * @param s Estudante com o qual se vai comparar.
     * @return true se os estudantes forem iguais, false caso contrário.
     */
    bool operator==(const Student& s) const;

    /**
     * @brief Sobrecarga do operador de comparação para determinar a ordem dos estudantes.
     * @param other Outro estudante com o qual se vai comparar.
     * @return true se o estudante atual for menor do que o outro, false caso contrário.
     */
    bool operator<(const Student& other) const;

    /**
     * @brief Devolve uma representação em cadeia de texto dos dados do estudante.
     * @return Cadeia de texto com os dados do estudante.
     */
    std::string print_Student();

    // Métodos

    /**
     * @brief Adiciona uma lição (Lesson) ao horário do estudante.
     * @param aula Lição que se vai adicionar ao horário do estudante.
     */
    void add_Lesson(Lesson aula);

    /**
     * @brief Remove uma lição (Lesson) do horário do estudante.
     * @param aula Lição que se vai remover do horário do estudante.
     */
    void remove_Lesson(Lesson aula);

    // Getters

    /**
     * @brief Obtém o código do estudante.
     * @return Código do estudante.
     */
    std::string get_StudentCode();

    /**
     * @brief Obtém o nome do estudante.
     * @return Nome do estudante.
     */
    std::string get_StudentName();

    /**
     * @brief Obtém o horário do estudante.
     * @return Horário do estudante (objeto Schedule).
     */
    Schedule get_Horario();

    /**
     * @brief Obtém uma lista das aulas do estudante.
     * @return Vetor de cadeias de texto que representa as aulas do estudante.
     */
    std::vector<std::string> get_classes();

private:
    std::string StudentCode;   ///< Código do estudante.
    std::string StudentName;   ///< O nome do estudante é o nome do estudante.
    Schedule horario_student;  ///< Horário do estudante (objeto Schedule).
};

#endif // AED_PROJECT_STUDENT_H
