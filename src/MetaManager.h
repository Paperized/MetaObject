#pragma once

#include <unordered_map>
#include <string>
#include <typeindex>

struct MetaObject
{
	std::string name;
	std::type_index value;

	MetaObject(std::string name, std::type_index value) : name(name), value(value) { }
	
	inline bool operator==(MetaObject const& other) const { return value == other.value; }
};

namespace std {
	template <>
	struct hash<MetaObject>
	{
		std::size_t operator()(const MetaObject& k) const
		{
			using std::size_t;
			using std::hash;
			using std::type_index;

			size_t res = 17;
			res = res * 31 + hash<type_index>()(k.value);
			return res;
		}
	};
}

struct MetaInfo
{
	std::unordered_map<std::string, std::string> meta_data;

	MetaInfo& AddMetaData(std::string name, std::string value)
	{
		if (meta_data.find(name) == meta_data.end())
		{
			meta_data.insert({ name, value });
		}

		return *this;
	}

	MetaInfo& ChangeMetaData(std::string name, std::string value)
	{
		if (meta_data.find(name) != meta_data.end())
		{
			meta_data[name] = value;
		}

		return *this;
	}

	std::string* GetMetaData(std::string name)
	{
		if (meta_data.find(name) == meta_data.end())
		{
			return nullptr;
		}

		return &meta_data[name];
	}

	MetaInfo& RemoveMetaData(std::string name)
	{
		if (meta_data.find(name) != meta_data.end())
		{
			meta_data.erase(name);
		}

		return *this;
	}
};

class MetaManager
{
public:

	template<class T> 
	MetaInfo& RegisterObject()
	{
		const std::type_info& t = typeid(T);
		MetaObject key(t.name(), std::type_index(t));

		if (meta_objects.find(key) == meta_objects.end())
		{
			MetaInfo new_meta;
			meta_objects.insert({ key, new_meta });
		}

		return meta_objects[key];
	}

	template<class T> 
	void UnregisterObject()
	{
		const std::type_info& t = typeid(T);
		MetaObject key(t.name(), std::type_index(t));

		if (meta_objects.find(key) != meta_objects.end())
		{
			meta_objects.erase(key);
		}
	}

	template<class T> 
	MetaInfo* GetMetaInfo()
	{
		const std::type_info& t = typeid(T);
		MetaObject key(t.name(), std::type_index(t));

		return meta_objects.find(key) != meta_objects.end() ? &meta_objects[key] : nullptr;
	}

	inline const int GetCountMetaObjects() const { return meta_objects.size(); }

	inline static MetaManager& GetManager()
	{
		static MetaManager instance;
		return instance;
	}

private:
	MetaManager() { }

private:
	std::unordered_map<MetaObject, MetaInfo> meta_objects;
};

static MetaManager& MetaMngr = MetaManager::GetManager();

#define UTILITY_META_OBJECT_METHODS(type)   static MetaInfo& AddMetaData(std::string name, std::string value) { return MetaMngr.GetMetaInfo<type>()->AddMetaData(name, value); } \
											static MetaInfo& ChangeMetaData(std::string name, std::string value) { return MetaMngr.GetMetaInfo<type>()->ChangeMetaData(name, value); } \
											static std::string* GetMetaData(std::string name) { return MetaMngr.GetMetaInfo<type>()->GetMetaData(name); } \
											static MetaInfo& RemoveMetaData(std::string name) { return MetaMngr.GetMetaInfo<type>()->RemoveMetaData(name); }
