#ifndef AED_PROJECT_LESSON_H
#define AED_PROJECT_LESSON_H

#include <string>

/**
 * @class Lesson
 * @brief Classe que representa uma lição, aula, ou período de ensino.
 */
class Lesson {
private:
    float start_hour; ///< Hora de início da lição.
    float duration;   ///< Duração da lição em horas.
    std::string Type; ///< Tipo de lição (por exemplo, aula teórica, prática).
    std::string Day;  ///< Dia da semana em que a lição ocorre.
    std::string UCcode; ///< Código da unidade curricular associada à lição.
    std::string ClassCode; ///< Código da turma da lição.
    std::string formathours(float hours);

public:
    /**
     * @brief Construtor que inicializa uma lição com os parâmetros fornecidos.
     * @param start_hour Hora de início da lição.
     * @param duration Duração da lição em horas.
     * @param Type Tipo de lição (por exemplo, aula teórica, prática).
     * @param Day Dia da semana em que a lição ocorre.
     * @param UCcode Código da unidade curricular associada à lição.
     * @param ClassCode Código da turma da lição.
     */
    Lesson(float start_hour, float duration, std::string Type, std. O Dia é o Dia, o UCcode é o Código da UC e o ClassCode é o Código da turma.
    ~Lesson(); ///< Destrutor da classe Lesson.

    // Operadores

    /**
     * @brief Sobrecarga do operador de igualdade para comparar duas lições.
     * @param l Lição com a qual se vai comparar.
     * @return true se as lições forem iguais, false caso contrário.
     */
    bool operator==(const Lesson& l) const;

    /**
     * @brief Sobrecarga do operador de comparação para determinar a ordem das lições.
     * @param other Outra lição com a qual se vai comparar.
     * @return true se a lição atual for anterior à outra, false caso contrário.
     */
    bool operator<(const Lesson& other) const;

    /**
     * @brief Retorna uma representação em cadeia de texto dos dados da lição.
     * @return Cadeia de texto com informações sobre a lição.
     */
    std::string print();

    // Getters

    /**
     * @brief Obtém a hora de início da lição.
     * @return Hora de início da lição.
     */
    float get_Start_hour();

    /**
     * @brief Obtém a duração da lição.
     * @return Duração da lição em horas.
     */
    float get_Duration();

    /**
     * @brief Obtém o tipo de lição.
     * @return Tipo de lição (por exemplo, aula teórica, prática).
     */
    std::string get_Type();

    /**
     * @brief Obtém o dia da semana da lição.
     * @return Dia da semana em que a lição ocorre.
     */
    std::string get_Day();

    /**
     * @brief Obtém o código da unidade curricular associada à lição.
     * @return Código da unidade curricular (UC).
     */
    std::string get_UCcode();

    /**
     * @brief Obtém o código da turma da lição.
     * @return Código da turma da lição.
     */
    std::string get_ClassCode();
};

#endif // AED_PROJECT_LESSON_H
