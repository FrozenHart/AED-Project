#ifndef AED_PROJECT_CLASS_H
#define AED_PROJECT_CLASS_H
#include <vector>
#include <string>
#include "Student.h"
#include "Schedule.h"

/**
 * @class Class
 * @brief Classe que representa uma turma de estudantes com informações sobre o horário, lista de estudantes e código da turma.
 */
class Class {
private:
    std::vector<Student> ListStudents; ///< Vetor de estudantes na turma.
    Schedule horario; ///< Horário da turma (objeto Schedule).
    std::string ClassCode; ///< Código da turma.

public:
    /**
     * @brief Construtor que inicializa uma turma com um horário, uma lista de estudantes e um código de turma.
     * @param horario_ Horário da turma (objeto Schedule).
     * @param Liststudents Lista de estudantes na turma.
     * @param ClassCode Código da turma.
     */
    Class(Schedule horario_, std::vector<Student> Liststudents, std::string ClassCode);

    /**
     * @brief Construtor que inicializa uma turma com um horário e um código de turma.
     * @param horario_ Horário da turma (objeto Schedule).
     * @param ClassCode Código da turma.
     */
    Class(Schedule horario_, std::string ClassCode);

    /**
     * @brief Destrutor da classe Class.
     */
    ~Class();

    /**
     * @brief Sobrecarga do operador de igualdade para comparar duas turmas.
     * @param c Turma com a qual se vai comparar.
     * @return true se as turmas forem iguais, false caso contrário.
     */
    bool operator==(const Class& c) const;

    // Métodos

    /**
     * @brief Adiciona uma aula ao horário da turma.
     * @param aula Aula a ser adicionada ao horário da turma.
     */
    void add_lesson(Lesson aula);

    /**
     * @brief Remove uma aula do horário da turma.
     * @param aula Aula a ser removida do horário da turma.
     */
    void remove_lesson(Lesson aula);

    /**
     * @brief Adiciona um estudante à lista de estudantes da turma.
     * @param student Estudante a ser adicionado à turma.
     */
    void add_student(Student student);

    // Getters

    /**
     * @brief Obtém o código da turma.
     * @return Código da turma.
     */
    std::string get_ClassCode();

    /**
     * @brief Obtém o horário da turma.
     * @return Horário da turma (objeto Schedule).
     */
    Schedule get_Schedule();

    /**
     * @brief Obtém a lista de estudantes na turma.
     * @return Vetor de estudantes na turma.
     */
    std::vector<Student> get_ListStudents();
};

#endif // AED_PROJECT_CLASS_H
