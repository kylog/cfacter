#include <facter/facts/array_value.hpp>
#include <rapidjson/document.h>
#include <yaml-cpp/yaml.h>

using namespace std;
using namespace rapidjson;
using namespace YAML;

namespace facter { namespace facts {

    void array_value::to_json(Allocator& allocator, rapidjson::Value& value) const
    {
        value.SetArray();

        for (auto const& element : _elements) {
            if (!element) {
                continue;
            }

            rapidjson::Value child;
            element->to_json(allocator, child);
            value.PushBack(child, allocator);
        }
    }

    ostream& array_value::write(ostream& os) const
    {
        // Write out the elements in the array
        os << "[ ";
        bool first = true;
        for (auto const& element : _elements) {
            if (!element) {
                continue;
            }
            if (first) {
                first = false;
            } else {
                os << ", ";
            }
            os << *element;
        }
        os << " ]";
        return os;
    }

    Emitter& array_value::write(Emitter& emitter) const
    {
        emitter << BeginSeq;
        for (auto const& element : _elements) {
            if (!element) {
                continue;
            }
            emitter << *element;
        }
        emitter << EndSeq;
        return emitter;
    }

}}  // namespace facter::facts
