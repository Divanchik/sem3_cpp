#pragma once

template <typename T>
struct Node
{
    T data;
    Node *next;
    Node *prev;
    /// Constructor
    Node(const T &new_data, Node *new_prev, Node *new_next) : data(new_data), next(new_next), prev(new_prev) {}
};

template <typename T>
class List;
template <typename T>
class list_iterator
{
    Node<T> *node;

public:
    list_iterator() : node(nullptr) {}                   /// Default constructor
    list_iterator(Node<T> *new_node) : node(new_node) {} /// Constructor
    ~list_iterator() {}
    list_iterator &operator++() /// Preincrenment
    {
        node = node->next;
        return *this;
    }
    list_iterator operator++(int) /// Postincrement
    {
        auto result(*this);
        node = node->next;
        return result;
    }
    list_iterator &operator--() /// Predecrement
    {
        node = node->prev;
        return *this;
    }
    list_iterator operator--(int) /// Postdecrement
    {
        auto result(*this);
        node = node->prev;
        return result;
    }
    T operator*() const { return node->data; }                               /// Dereferentiation
    T &operator*() { return node->data; }                                    /// Dereferentiation
    Node<T> *operator->() { return node; }                                   /// Member access operator
    bool operator==(const list_iterator &a) const { return node == a.node; } /// Equality operator
    bool operator!=(const list_iterator &a) const { return node != a.node; } /// Inequality operator

    friend class List<T>;
};

template <typename T>
/// List class
class List
{
    Node<T> *_head;
    Node<T> *_tail;
    Node<T> *_void; /// Past-the-end Node
    size_t _size;   /// Size of list

    void log(const char *message) { std::cout << message << std::endl; }

public:
    using const_iterator = const list_iterator<T>;
    using iterator = list_iterator<T>;

    bool empty() const noexcept { return _size == 0 ? true : false; }
    size_t size() const noexcept { return _size; }

    /// Default constructor
    List() : _head(nullptr), _tail(nullptr), _void(new Node<T>(T(), nullptr, nullptr)), _size(0)
    {
        log("Default constructor!");
        _void->next = _void;
        _void->prev = _void;
    }
    /// Size constructor \param[in] new_size New size of list
    List(size_t new_size) : _head(nullptr), _tail(nullptr), _void(new Node<T>(T(), nullptr, nullptr)), _size(0)
    {
        log("Size constructor!");
        _void->next = _void;
        _void->prev = _void;
        resize(new_size);
    }
    /// Copy constructor \param[in] a List
    List(const List<T> &a) : _head(nullptr), _tail(nullptr), _void(new Node<T>(T(), nullptr, nullptr)), _size(0)
    {
        log("Copy constructor!");
        _void->next = _void;
        _void->prev = _void;

        auto tmp = a.begin();
        for (size_t i=0;i<a.size();i++)
        {
            insert(end(), *tmp);
            tmp++;
        }
    }
    /// Move constructor \param[in] a List
    List(List &&a) : _head(nullptr), _tail(nullptr), _void(new Node<T>(T(), nullptr, nullptr)), _size(0)
    {
        log("Move constructor!");
        _void->next = _void;
        _void->prev = _void;
        swap(a);
    }
    /// Assign copy operator \param[in] a List
    List<T> &operator=(const List<T> &a)
    {
        log("Copy assignment!");
        clear();
        _void = new Node<T>(T(), nullptr, nullptr);
        _void->next = _void;
        _void->prev = _void;

        auto tmp = a.begin();
        for (size_t i=0;i<a.size();i++)
        {
            insert(end(), *tmp);
            tmp++;
        }
        return *this;
    }
    /// Assign move operator \param[in] a List
    List<T> &operator=(List<T> &&a)
    {
        log("Move assignment!");
        clear();
        _void = new Node<T>(T(), nullptr, nullptr);
        _void->next = _void;
        _void->prev = _void;

        swap(a);
        return *this;
    }
    /// Destructor
    ~List()
    {
        log("Destructor!");
        clear();
    }

    /// Swap \param[in, out] a List
    void swap(List<T> &a)
    {
        log("Swap!");
        std::swap(_head, a._head);
        std::swap(_tail, a._tail);
        std::swap(_size, a._size);
    }
    /// Clear the list
    void clear()
    {
        log("Clear!");
        std::cout << "\\Initial size: " << _size << std::endl;
        Node<T> *tmp = _head;
        if (_size != 0)
        {
            while (_head != _tail)
            {
                tmp = _head;
                _head = _head->next;
                std::cout << " |delete " << tmp->data << std::endl;
                delete tmp;
            }
            delete _head;
            _size = 0;
        }
        _head = nullptr;
        _tail = nullptr;
        delete _void;
    }
    /**
     * Access operator
     * \param[in] index Index of element
     */
    T operator[](size_t index) const
    {
        if (index >= _size)
            throw "IndexError: Index out of range!";
        Node<T> *tmp = _head;
        for (size_t i = 0; i != index; i++)
            tmp = tmp->next;
        return tmp->data;
    }
    /**
     * Access operator
     * \param[in] index Index of element
     */
    T &operator[](size_t index)
    {
        if (index >= _size)
            throw "IndexError: Index out of range!";
        Node<T> *tmp = _head;
        for (size_t i = 0; i != index; i++)
            tmp = tmp->next;
        return tmp->data;
    }

    /// \return Constant begin iterator
    const_iterator begin() const noexcept { return list_iterator<T>(_head); }
    /// \return Constant past-the-end iterator
    const_iterator end() const noexcept { return list_iterator<T>(_void); }
    /// \return Begin iterator
    iterator begin() noexcept { return list_iterator<T>(_head); }
    /// \return Past-the-end iterator
    iterator end() noexcept { return list_iterator<T>(_void); }

    /// Insert method
    const_iterator insert(const list_iterator<T> &pos, const T &data)
    {
        std::cout << "Insert " << data;
        if (_size == 0)
        {
            _head = new Node<T>(data, _void, _void);
            _tail = _head;
        }
        else if (pos == begin())
        {
            Node<T> *tmp = new Node<T>(data, _void, _head);
            tmp->next->prev = tmp;
            _head = tmp;
        }
        else if (pos == end())
        {
            Node<T> *tmp = new Node<T>(data, _tail, _void);
            tmp->prev->next = tmp;
            _tail = _tail->next;
        }
        else
        {
            Node<T> *tmp = new Node<T>(data, pos.node->prev, pos.node);
            tmp->next->prev = tmp;
            tmp->prev->next = tmp;
        }
        _size += 1;
        std::cout << " " << _size << std::endl;
        return list_iterator<T>(pos.node->prev);
    }
    /// Erase method
    const_iterator erase(const list_iterator<T> &pos)
    {
        std::cout << "Erase " << pos.node->data;
        Node<T> *ret;
        if (_size == 1)
        {
            delete _head;
            _head = nullptr;
            _tail = nullptr;
            ret = nullptr;
        }
        else if (pos == begin())
        {
            _head = _head->next;
            delete _head->prev;
            _head->prev = _void;
            ret = _head;
        }
        else if (pos == end())
        {
            _tail = _tail->prev;
            delete _tail->next;
            _tail->next = _void;
            ret = _tail;
        }
        else
        {
            Node<T> *tmp = pos.node;
            ret = tmp->next;
            tmp->next->prev = tmp->prev;
            tmp->prev->next = tmp->next;
            delete tmp;
        }
        _size -= 1;
        std::cout << " " << _size << std::endl;
        return list_iterator<T>(ret);
    }
    /**
     * Change size of List
     * \param[in] new_size New size of list
     */
    void resize(size_t new_size)
    {
        std::cout << "Resize " << _size << " -> " << new_size << std::endl;
        if (new_size > 10000000)
            throw "MemoryError: Too many memory requested!";
        while (_size != new_size)
        {
            if (_size > new_size)
                erase(end());
            else if (new_size > _size)
                insert(end(), T());
        }
    }
};