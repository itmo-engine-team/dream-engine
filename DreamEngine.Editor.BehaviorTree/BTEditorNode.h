#pragma once

#include <vector>
#include "imgui.h"

#include "Serializable.h"
#include "BTNodeType.h"

class BTEditorNode : Serializable
{

public:

    BTEditorNode(BTNodeType type);
    virtual ~BTEditorNode();

    int GetId() const;
    void SetId(int id);

    const std::string& GetName() const;
    void SetName(const std::string& name);

    std::pair<int, BTEditorNode*> GetParentLink() const;
    void SetParentLink(std::pair<int, BTEditorNode*> parentLink);

    const std::vector<std::pair<int, BTEditorNode*>>& GetChildrenLinks() const;
    void AddChildLink(std::pair<int, BTEditorNode*> childLink);

    virtual bool CanHaveParent() = 0;
    virtual bool CanHaveChild() = 0;
    virtual bool CanHaveChildren() = 0; // Can have one or more children

protected:

    Json toJson() override;
    void fromJson(Json json) override;

private:

    BTNodeType type;
    int id;
    std::string name;
    ImVec2 position;

    std::pair<int, BTEditorNode*> parentLink;
    std::vector<std::pair<int, BTEditorNode*>> childrenLinks;

};

