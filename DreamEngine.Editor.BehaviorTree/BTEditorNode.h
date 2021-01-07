#pragma once

#include <vector>
#include "imgui.h"

#include "Serializable.h"
#include "BTNodeType.h"

class BehaviorTreeEditor;

class BTEditorNode : Serializable
{

public:

    BTEditorNode(BTNodeType type);
    virtual ~BTEditorNode();

    int GetId() const;
    const std::string& GetName() const;
    const ImVec2& GetPosition() const;

    int GetParentAttributeId() const;
    std::pair<int, BTEditorNode*> GetParentLink() const;

    int GetChildrenAttributeId() const;
    const std::vector<std::pair<int, BTEditorNode*>>& GetChildrenLinks() const;

    virtual bool CanHaveParent() = 0;
    virtual bool CanHaveChild() = 0;
    virtual bool CanHaveChildren() = 0; // Can have one or more children

protected:

    friend BehaviorTreeEditor;

    void setId(int id);
    void setName(const std::string& name);
    void setPosition(ImVec2 position);

    void setParentAttributeId(int attributeId);
    void setParentLink(std::pair<int, BTEditorNode*> parentLink);

    void addChildLink(std::pair<int, BTEditorNode*> childLink);
    void setChildrenAttributeId(int attributeId);

    Json toJson() override;
    void fromJson(Json json) override;

private:

    BTNodeType type;
    int id;
    std::string name;
    ImVec2 position;

    int parentAttributeId = -1;
    std::pair<int, BTEditorNode*> parentLink;

    int childrenAttributeId = -1;
    std::vector<std::pair<int, BTEditorNode*>> childrenLinks;

};

