# Smart Shared and Weak Pointers

This project provides a simple implementation of smart shared and weak pointers in C++. The implementation consists of two main classes: `SharedPtr` and `WeakPtr`.

## SharedPtr Class

The `SharedPtr` class represents a shared pointer that manages the lifetime of a dynamically allocated object. It uses reference counting to keep track of the number of `SharedPtr` instances pointing to the same resource. The resource is deleted only when the last `SharedPtr` pointing to it is destroyed or reset.

The `SharedPtr` class provides the following functionalities:

- Constructing a `SharedPtr` object with a raw pointer to a resource.
- Copy constructing a `SharedPtr` object from another `SharedPtr` object.
- Assigning a `SharedPtr` object to another `SharedPtr` object.
- Resetting the `SharedPtr` object to manage a new resource or nullptr.
- Swapping the managed object with another `SharedPtr` object.
- Accessing the managed resource using the dereference and arrow operators.
- Getting the number of `SharedPtr` objects managing the resource.

## WeakPtr Class

The `WeakPtr` class represents a weak pointer that provides a non-owning reference to a resource managed by a `SharedPtr`. Unlike `SharedPtr`, `WeakPtr` does not participate in ownership, and it does not prevent the resource from being deleted. It can be used to check the validity of the resource and obtain a `SharedPtr` object to it.

The `WeakPtr` class provides the following functionalities:

- Constructing a `WeakPtr` object.
- Copy constructing a `WeakPtr` object from another `WeakPtr` object or a `SharedPtr` object.
- Assigning a `WeakPtr` object to another `WeakPtr` object or a `SharedPtr` object.
- Resetting the `WeakPtr` object to null.
- Swapping the `WeakPtr` object with another `WeakPtr` object.
- Getting the number of `SharedPtr` objects managing the resource.
- Checking if the resource has expired (i.e., no `SharedPtr` object managing it).
- Attempting to obtain a `SharedPtr` object to the resource using the `Lock` function.

## Usage Example

An example usage of the `SharedPtr` and `WeakPtr` classes is provided in the `main.cpp` file. It demonstrates how to create, copy, assign, reset, and swap shared and weak pointers. The example includes a simple `Test` class, and it prints messages to illustrate the lifecycle and usage of the pointers.

To compile and run the example:

1. Make sure you have a C++ compiler installed.
2. Compile the source files using the command: `g++ -o main main.cpp`
3. Run the executable: `./main`

The output will show the creation and destruction of objects, as well as the usage of shared and weak pointers.

Feel free to explore the implementation in the `Shared_Ptr.h` and `Weak_Ptr.h` header files to understand the details of the classes.

## Future Enhancements
This implementation provides a basic understanding of shared and weak pointers. However, it is not a complete replacement for the standard library std::shared_ptr and std::weak_ptr. Here are some potential future enhancements:

1. Thread safety: Consider adding thread safety mechanisms to ensure correct behavior in multi-threaded environments.
2. Additional functionality: Expand the implementation to include features like custom deleters, support for arrays, and other utility functions.
3. Testing: Develop a comprehensive test suite to validate the implementation's correctness and edge cases.

## Contribution
Contributions to the project are welcome! If you have any ideas, bug reports, or feature requests, please feel free to submit them.

Enjoy exploring the smart shared and weak pointers implementation! If you have any questions or feedback, please feel free to reach out.
