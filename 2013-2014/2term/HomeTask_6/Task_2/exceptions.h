#pragma once

/**
 * @brief The Exceptions class
 * @detailed Consists of exceptions
 */
class Exceptions
{
public:
    /**
     * @brief The AddsExistingValue class
     * @detailed Throws, when trying to add value, that already added
     */
    class AddsExistingValue{};
    /**
     * @brief The DeletesNotExistingValue class
     * @detailed Throws, when trying to delete value, that not added yet
     */
    class DeletesNotExistingValue{};
};
