#pragma once

template <typename T>
class Vector
{
    /// Data array
    T *_data;
    /// Size of used space
    size_t _size;
    /// Size of actual space
    size_t _capacity;

    void log(const char *message) { std::cout << message << std::endl; }

public:
    using iterator = T *;
    using const_iterator = const T *;

    /// \return 'true' if list is empty
    bool empty() const noexcept { return (_size == 0 ? true : false); }
    /// \return Size of used space
    size_t size() const noexcept { return _size; }

    /// Default constructor
    Vector() : _data(nullptr), _size(0), _capacity(0) {log("Default constructor!");}
    /// Size constructor \param[in] new_size New size of array
    Vector(size_t new_size) : _data(new T[new_size + 1]), _size(new_size), _capacity(new_size + 1) {log("Size constructor!");}
    /// Copy constructor \param[in] a Vector
    Vector(const Vector<T> &a) : _data(new T[a._capacity]), _size(a._size), _capacity(a._capacity)
    {
        log("Copy constructor!");
        for (size_t i = 0; i < _size; ++i)
            _data[i] = a[i];
    }
    /// Move constructor \param[in] a Vector
    Vector(Vector<T> &&a) noexcept : _data(a._data), _size(a._size), _capacity(a._capacity)
    {
        log("Move constructor!");
        a._data = nullptr;
        a._size = 0;
        a._capacity = 0;
    }
    /// Assign copy operator \param[in] a Vector
    Vector<T> &operator=(const Vector<T> &a)
    {
        log("Copy assignment!");
        Vector<T> tmp(a);
        swap(tmp);
        return *this;
    }
    /// Assign move operator \param[in] a Vector
    Vector<T> &operator=(Vector<T> &&a) noexcept
    {
        log("Move assignment!");
        swap(a);
        a._data = nullptr;
        a._size = 0;
        a._capacity = 0;
        return *this;
    }
    /// Destructor
    ~Vector()
    {
        log("Destructor!");
        delete[] _data;
    }
    /// Swap \param[in, out] a Vector
    void swap(Vector<T> &a) noexcept
    {
        log("Swap!");
        std::swap(_data, a._data);
        std::swap(_size, a._size);
        std::swap(_capacity, a._capacity);
    }
    /// Clear the vector
    void clear() noexcept
    {
        log("Clear!");
        if (_capacity == 0)
            return;
        delete[] _data;
        _data = nullptr;
        _size = 0;
        _capacity = 0;
    }
    /**
     * Access operator
     * \param[in] index Index of element
     */
    T &operator[](size_t index)
    {
        if (index >= _size)
            throw "Access error: Index out of range!";
        // std::cout << "Access to [" << index << "] element!" << std::endl;
        return _data[index];
    }
    /**
     * Access operator
     * \param[in] index Index of element
     */
    T operator[](size_t index) const
    {
        if (index >= _size)
            throw "Access error: Index out of range!";
        // std::cout << "Access to value of [" << index << "] element!" << std::endl;
        return _data[index];
    }
    /// \return Constant iterator to beginning
    const_iterator begin() const { return _data; }
    /// \return Iterator to end
    const_iterator end() const { return _data + _size; }
    /// \return Iterator to beginning
    iterator begin() { return _data; }
    /// \return Iterator to end
    iterator end() { return _data + _size; }
    /// Insert method
    iterator insert(const_iterator pos, const T &value)
    {
        std::cout << "Insert " << value << " " << pos - (const_iterator)_data << std::endl;
        if (pos == end())
        {
            std::cout << "Inserting element in the end!" << std::endl;
            resize(_size + 1);
            _data[_size - 1] = value;
            return _data + _size - 1;
        }
        std::cout << "Inserting element!" << std::endl;
        resize(_size + 1);
        const_iterator tmp = _data;
        int index = (int)(pos - tmp);
        std::cout << "Index: " << index << std::endl;
        for (int i=_size - 2; i >= index; i--)
            _data[i+1] = std::move_if_noexcept(_data[i]);
        _data[index] = value;
        return _data + index;
    }
    /// Erase method
    iterator erase(const_iterator pos)
    {
        log("Erase!");
        if (pos == end())
        {
            _data[_size] = 0;
            resize(_size - 1);
            return _data + _size - 1;
        }
        size_t index = pos - (const_iterator)_data;
        for (size_t i = index; i < _size - 1; i++)
            _data[i] = std::move_if_noexcept(_data[i + 1]);
        resize(_size - 1);
        return _data;
    }
    /**
     * Change size of Vector
     * \param[in] new_size New size of array
     */
    void resize(size_t new_size)
    {
        std::cout << "Resize " << _size << " -> " << new_size << std::endl;
        if (new_size > 10000000)
            throw "MemoryError: Too many memory requested!";
        if (empty())
        {
            _capacity = new_size + 100;
            _data = new T[_capacity];
            _size = new_size;
        }
        else
        {
            if (new_size <= _capacity - 1)
                _size = new_size;
            else
            {
                T *tmp = new T[new_size + 100];
                for (size_t i = 0; i < _size; i++)
                    tmp[i] = _data[i];
                clear();
                _data = tmp;
                _size = new_size;
                _capacity = new_size + 100;
            }
        }
    }
};
