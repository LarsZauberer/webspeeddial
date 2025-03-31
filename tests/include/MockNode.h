#ifndef MockNode_h_INCLUDED
#define MockNode_h_INCLUDED

#include "webspeeddial/INode.h"
#include <gmock/gmock.h>
class MockNode : public core::INode {
    public:
        MOCK_METHOD(bool, is_defined, ()); 
        MOCK_METHOD(bool, is_sequence, ()); 
        MOCK_METHOD(std::string, as_string, ());
        MOCK_METHOD(INode*, get, (std::string&&));
        MOCK_METHOD(INode*, get, (size_t));
        MOCK_METHOD(void, set, (std::string&&, INode&));
        MOCK_METHOD(void, set, (std::string&&, std::string&));
        MOCK_METHOD(void, push_back, (INode&));
        MOCK_METHOD(void, push_back, (std::string&));
        MOCK_METHOD(void, write, (std::ofstream &));
};

#endif // MockNode_h_INCLUDED
