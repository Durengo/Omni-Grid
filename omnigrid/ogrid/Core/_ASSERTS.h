#pragma once

template <typename T>
void _IS_PTR_NULL_(T *ptr)
{
    CLI_ASSERT(ptr != nullptr, "Pointer is null");
}

template <typename Derived, typename Base>
Derived _DYNAMIC_CAST_(Base *ptr)
{
    _IS_PTR_NULL_(ptr);
    Derived casted_ptr = dynamic_cast<Derived>(ptr);
    _IS_PTR_NULL_(casted_ptr);
    return casted_ptr;
}