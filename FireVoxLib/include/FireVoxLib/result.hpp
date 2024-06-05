//
// Created by Pugemon on 19.05.2024.
//

#ifndef FIREVOXLIB_RESULT_HPP
#define FIREVOXLIB_RESULT_HPP

#include "types.hpp"

/**
 * @brief Проверяет, указывает ли описание кода результата на успех.
 *
 * @param res Код результата типа Result для проверки.
 * @return true, если код результата указывает на успех, иначе false.
 */
#define R_SUCCEEDED(res)   ((((res)>>9)&0x1FFF)==0)

/**
 * @brief Проверяет, указывает ли описание кода результата на неудачу.
 *
 * @param res Код результата типа Result для проверки.
 * @return true, если код результата указывает на неудачу, иначе false.
 */
#define R_FAILED(res)      ((((res)>>9)&0x1FFF)!=0)

/**
 * @brief Выполняет выражение и возвращает результат, если он указывает на неудачу.
 * @author root2nul
 *
 * Этот макрос выполняет заданное выражение и проверяет результат с помощью макроса `R_FAILED`.
 * Если результат указывает на неудачу (failure), то макрос немедленно возвращает этот результат
 * из текущей функции. Это удобно для упрощения кода проверки ошибок и упрощает управление
 * ошибками в функциях.
 *
 * @param what Выражение, возвращающее значение типа Result, которое нужно проверить.
 *
 * @example
 * Result someFunction() {
 *     R_TRY(someOtherFunction());
 *     // Дополнительный код, если someOtherFunction() успешно выполнен
 *     return MAKERESULT(Module_Graphics, Success);
 * }
 */
#define R_TRY(what) do { Result result = (what); if (R_FAILED(result)) return result; } while (0)

/**
 * @brief Возвращает идентификатор модуля из кода результата.
 *
 * @param res Код результата типа Result.
 * @return Идентификатор модуля.
 */
#define R_MODULE(res)      ((res)&0x1FF)

/**
 * @brief Возвращает описание кода результата.
 *
 * Этот макрос извлекает описание из заданного кода результата.
 *
 * @param res Код результата типа Result.
 * @return Описание кода результата.
 */
#define R_DESCRIPTION(res) (((res)>>9)&0x1FFF)

/**
 * @brief Маскирует неиспользуемые биты в коде результата, извлекая фактическое значение для использования в сравнениях.
 *
 * @param res Код результата типа Result.
 * @return Значение кода результата без неиспользуемых битов.
 */
#define R_VALUE(res)       ((res)&0x3FFFFF)

/**
 * @brief Создает код результата из его составных компонентов.
 *
 * Этот макрос создает код результата, используя идентификатор модуля и описание.
 *
 * @param module Идентификатор модуля типа Modules.
 * @param description Описание кода результата типа {MODULE_NAME}_Errors.
 * @return Составной код результата типа Result.
 */
#define MAKERESULT(module, description) \
     ((((module)&0x1FF)) | ((description)&0x1FFF)<<9)


/// Module values
enum Modules
{
    Module_VulWalk = 0,
    Module_Graphics = 256,
    Module_Audio = 356,
    Module_Unknown = 511
};

enum VulWalk_Errors
{
    Succes = 0,
};

enum Graphics_Errors
{
    Success = 0,
    NormalTerminate,
    FailedToInitializeGLFW = 257,
    FailedToInitializeGLAD,
    FailedToCreateWindow,
    FailedToCompileShader,
    Unknown = 355
};


#endif //FIREVOXLIB_RESULT_HPP
