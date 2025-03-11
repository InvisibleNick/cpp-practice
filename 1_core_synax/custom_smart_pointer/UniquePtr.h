#include <utility>
#include <stdexcept>

// A simple implementation of a unique pointer to manage dynamic memory.
template <typename T>
class UniquePtr {
    private:
        T* ptr;  // Raw pointer to manage the allocated object.

    public:
        // Constructor: Takes ownership of a raw pointer.
        explicit UniquePtr(T* p = nullptr) noexcept : ptr(p) {}

        // Move constructor: Transfers ownership from another UniquePtr.
        // Ensures only one UniquePtr instance owns the resource at a time.
        UniquePtr(UniquePtr&& other) noexcept : ptr(std::exchange(other.ptr, nullptr)) {}

        // Destructor: Ensures the owned object is deleted when UniquePtr goes out of scope.
        ~UniquePtr() {
            delete ptr;
        }

        // Disable copy semantics to enforce unique ownership.
        UniquePtr(const UniquePtr&) = delete;
        UniquePtr& operator=(const UniquePtr&) = delete;

        // Overloaded -> operator to allow access to the owned object's members.
        T* operator->() const noexcept {
            return ptr;
        }

        // Boolean conversion operator to check if UniquePtr holds a valid pointer.
        explicit operator bool() const noexcept {
            return ptr != nullptr;
        }

        // Overloaded * operator to allow dereferencing the unique pointer.
        // Throws an exception if ptr is null to avoid dereferencing invalid memory.
        T& operator*() const {
            if (!ptr) {
                throw std::runtime_error("Attempted to dereference a null UniquePtr");
            }
            return *ptr;
        }

        // Returns the raw pointer without transferring ownership.
        T* get() const noexcept {
            return ptr;
        }

        // Releases ownership of the managed object and returns the raw pointer.
        // The caller is responsible for managing the returned pointer.
        T* release() noexcept {
            return std::exchange(ptr, nullptr);
        }

        // Resets the unique pointer with a new raw pointer.
        // Deletes the existing object before taking ownership of the new pointer.
        void reset(T* p = nullptr) noexcept {
            if (ptr != p) {  // Prevent self-resetting.
                delete ptr;
                ptr = p;
            }
        }

        // Move assignment operator: Transfers ownership from another UniquePtr.
        // Ensures the previously owned resource is safely deleted before transfer.
        UniquePtr& operator=(UniquePtr&& other) noexcept {
            if (this != &other) {
                reset(std::exchange(other.ptr, nullptr));
            }
            return *this;
        }
};
