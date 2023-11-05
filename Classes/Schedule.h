#ifndef AED_PROJECT_SCHEDULE_H
#define AED_PROJECT_SCHEDULE_H
#include "Lesson.h"
#include <vector>

/**
 * @class Schedule
 * @brief Classe que representa um horário de aulas.
 */
class Schedule {
private:
    std::vector<Lesson> horario; ///< Vetor de aulas no horário.
    std::string formathours(float hours);

public:
    /**
     * @brief Construtor padrão que inicializa um horário vazio.
     */
    Schedule();

    /**
     * @brief Destrutor da classe Schedule.
     */
    ~Schedule();

    /**
     * @brief Construtor que inicializa um horário com um vetor de aulas.
     * @param horario Vetor de aulas a ser associado ao horário.
     */
    Schedule(std::vector<Lesson> horario);

    // Operadores

    /**
     * @brief Sobrecarga do operador de igualdade para comparar dois horários.
     * @param s Horário com o qual se vai comparar.
     * @return true se os horários forem iguais, false caso contrário.
     */
    bool operator==(const Schedule& s) const;

    /**
     * @brief Retorna uma representação em cadeia de texto do horário.
     * @return Cadeia de texto com informações sobre as aulas no horário.
     */
    std::string print();

    // Getters

    /**
     * @brief Obtém o vetor de aulas no horário.
     * @return Vetor de aulas no horário.
     */
    std::vector<Lesson> get_Schedule();

    // Métodos

    /**
     * @brief Adiciona uma aula ao horário.
     * @param aula Aula a ser adicionada ao horário.
     */
    void add_Lesson(Lesson aula);

    /**
     * @brief Remove uma aula do horário.
     * @param aula Aula a ser removida do horário.
     */
    void remove_Lesson(Lesson aula);

    /**
     * @brief Ordena as aulas no horário com base em algum critério específico.
     */
    void sorted();
};

#endif // AED_PROJECT_SCHEDULE_H
