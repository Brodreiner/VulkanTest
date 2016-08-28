

template <typename T>
class VDeleter {
public:
	VDeleter() : VDeleter([](T, VkAllocationCallbacks*) {}) {}

	VDeleter(std::function<void(T, VkAllocationCallbacks*)> deletef) {
		this->deleter = [=](T obj) { deletef(obj, nullptr); };
	}

	VDeleter(const VDeleter<VkInstance>& instance, std::function<void(VkInstance, T, VkAllocationCallbacks*)> deletef) {
		this->deleter = [&instance, deletef](T obj) { deletef(instance, obj, nullptr); };
	}

	VDeleter(const VDeleter<VkDevice>& device, std::function<void(VkDevice, T, VkAllocationCallbacks*)> deletef) {
		this->deleter = [&device, deletef](T obj) { deletef(device, obj, nullptr); };
	}

	~VDeleter() {
		cleanup();
	}

	T* operator &() {
		cleanup();
		return &object;
	}

	operator T() const {
		return object;
	}

private:
	T object{ VK_NULL_HANDLE };
	std::function<void(T)> deleter;

	void cleanup() {
		if (object != VK_NULL_HANDLE) {
			deleter(object);
		}
		object = VK_NULL_HANDLE;
	}
};

//
//
//
//
//
//
//
//
//
////
////
////
////template<>
////class VDeleter<VkInstance>
////{
////public:
////	VDeleter() : VDeleter([](VkInstance, VkAllocationCallbacks*) {}) {}
////
////	VDeleter(std::function<void(VkInstance, VkAllocationCallbacks*)> deletef) {
////		this->deleter = [=](VkInstance obj) { deletef(obj, nullptr); };
////	}
////
////	VDeleter(const VDeleter<VkInstance>& instance, std::function<void(VkInstance, VkInstance, VkAllocationCallbacks*)> deletef) {
////		this->deleter = [&instance, deletef](VkInstance obj) { deletef(instance, obj, nullptr); };
////	}
////
////	VDeleter(const VDeleter<VkDevice>& device, std::function<void(VkDevice, VkInstance, VkAllocationCallbacks*)> deletef) {
////		this->deleter = [&device, deletef](VkInstance obj) { deletef(device, obj, nullptr); };
////	}
////
////	~VDeleter() {
////	//	cleanup();
////	}
////
////	VkInstance* operator &() {
////		cleanup();
////		return &object;
////	}
////
////	operator VkInstance() const {
////		return object;
////	}
////
////private:
////	VkInstance object{ VK_NULL_HANDLE };
////	std::function<void(VkInstance)> deleter;
////
////	void cleanup() {
////		if (object != VK_NULL_HANDLE) {
////			deleter(object);
////		}
////		object = VK_NULL_HANDLE;
////	}
////};
////
//
//
//
//
//
//
//template<>
//class VDeleter<VkSwapchainKHR>
//{
//public:
//	VDeleter(const VkDevice& device) : m_device(device)
//	{
//		std::cout << device << std::endl;
//	}
//
//	~VDeleter() {
//		cleanup();
//	}
//
//	VkSwapchainKHR* operator &() {
//		cleanup();
//		return &m_object;
//	}
//
//	operator VkSwapchainKHR() const {
//		return m_object;
//	}
//
//	operator const VkSwapchainKHR&() const {
//		return m_object;
//	}
//
//private:
//	const VkDevice& m_device;
//	VkSwapchainKHR m_object{ VK_NULL_HANDLE };
//
//	void cleanup() {
//		if (m_object != VK_NULL_HANDLE) vkDestroySwapchainKHR(m_device, m_object, nullptr);
//		m_object = VK_NULL_HANDLE;
//	}
//};
