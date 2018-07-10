#include <memory>

template<typename T>
class maybe_ptr
{
public:
  using value_type = T;
  using observer_type = T*;
  using owning_type = std::unique_ptr<T>;

  maybe_ptr() :
    m_own(nullptr),
    m_ref(nullptr)
  {}

  explicit maybe_ptr(owning_type&& own) :
    m_own(std::move(own)),
    m_ref(m_own.get())
  {
  }

  explicit maybe_ptr(observer_type ref) :
    m_own(nullptr),
    m_ref(ref)
  {}

  maybe_ptr(maybe_ptr&& other) :
    m_own(std::move(other.m_own)),
    m_ref(other.m_ref)
  {
    other.m_ref = other.m_own.get();
  }

  template<class U>
  maybe_ptr(maybe_ptr<U>&& other) :
    m_own(std::move(other.m_own)),
    m_ref(other.m_ref)
  {
    other.m_ref = other.m_own.get();
  }

  maybe_ptr& operator=(maybe_ptr&& r)
  {
    m_own = std::move(r.m_own);
    m_ref = r.m_ref;
    r.m_ref = r.m_own.get();
    return *this;
  }

  template<class U>
  maybe_ptr& operator=(maybe_ptr<U>&& r)
  {
    m_own = std::move(r.m_own);
    m_ref = r.m_ref;
    r.m_ref = r.m_own.get();
    return *this;
  }

  maybe_ptr& operator=(std::nullptr_t)
  {
    m_own = nullptr;
    m_ref = nullptr;
    return *this;
  }

  /* Observers */

  bool is_owning() const
  {
    return m_own != nullptr;
  }

  observer_type get()
  {
    return m_ref;
  }

  const observer_type get() const
  {
    return m_ref;
  }

  explicit operator bool() const
  {
    return m_ref == nullptr;
  }

  typename std::add_lvalue_reference<value_type>::type operator*() const
  {
    return *m_ref;
  }

  observer_type operator->() const
  {
    return m_ref;
  }

  /* Modifiers */

  owning_type release()
  {
    m_ref = nullptr;
    return std::move(m_own);
  }

  void reset(owning_type&& new_owner = owning_type(nullptr))
  {
    m_own.swap(new_owner);
    m_ref = m_own.get();
  }

  void reset(observer_type new_observer)
  {
    m_own.reset(nullptr);
    m_ref = new_observer;
  }

  void swap(maybe_ptr<value_type> other)
  {
    m_own.swap(other.m_own);
    std::swap(m_ref, other.m_ref);
  }

private:
  owning_type m_own;
  observer_type m_ref;

  template<class U>
  friend class maybe_ptr;
};

template<class T>
bool operator==(const maybe_ptr<T>& x, std::nullptr_t) noexcept
{
  return x.get() == nullptr;
}

template<class T>
bool operator==(std::nullptr_t, const maybe_ptr<T>& x) noexcept
{
  return nullptr == x.get();
}

template<class T>
bool operator!=(const maybe_ptr<T>& x, std::nullptr_t) noexcept
{
  return x.get() != nullptr;
}

template<class T>
bool operator!=(std::nullptr_t, const maybe_ptr<T>& x) noexcept
{
  return nullptr != x.get();
}

template<class T, class... Args>
maybe_ptr<T> make_owner( Args&&... args )
{
  return maybe_ptr<T>(std::make_unique<T>(std::forward<Args>(args)...));
}

template<typename T>
maybe_ptr<T> make_observer(T* observer)
{
  return maybe_ptr<T>(observer);
}

template<typename T, typename U>
maybe_ptr<T> make_observer(U* observer)
{
  return maybe_ptr<T>(observer);
}

template<class T>
maybe_ptr<T> make_observer(const maybe_ptr<T>& observee)
{
  return maybe_ptr<T>(observee.get());
}

template<class T, class U>
maybe_ptr<T> make_observer(const maybe_ptr<U>& observee)
{
  return maybe_ptr<T>(observee.get());
}

template<class T>
maybe_ptr<T> to_owner(const maybe_ptr<T>& observer)
{
  return make_owner<T>(*observer);
}

template<class T, class U>
maybe_ptr<T> to_owner(const maybe_ptr<U>& observer)
{
  return make_owner<T>(*observer);
}

template<class T>
void into_owner(maybe_ptr<T>& observer)
{
  observer.reset(std::make_unique<T>(*observer));
}
