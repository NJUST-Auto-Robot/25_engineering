#include "behavior_tree.h"

/**
 * @brief 顺序器（SEQUENCE）执行逻辑
 *
 * @param node
 * @return BTStatus
 */
static BTStatus sequence_excutor(BTNode *node)
{
    while (node->current_index < node->child_count)
    {
        BTStatus status = node->children[node->current_index]->bt_callback(node->children[node->current_index]);
        if (status == BT_RUNNING)
            return BT_RUNNING;
        if (status == BT_FAILURE)
        {
            node->current_index = 0;
            return BT_FAILURE;
        }
        node->current_index++;
    }
    node->current_index = 0;
    return BT_SUCCESS;
}

/**
 * @brief 选择器（SELECTOR）执行逻辑
 *
 * @param node
 * @return BTStatus
 */
static BTStatus selector_excutor(BTNode *node)
{
    while (node->current_index < node->child_count)
    {
        BTStatus status = node->children[node->current_index]->bt_callback(node->children[node->current_index]);
        if (status == BT_RUNNING)
            return BT_RUNNING;
        if (status == BT_SUCCESS)
        {
            node->current_index = 0;
            return BT_SUCCESS;
        }
        node->current_index++;
    }
    node->current_index = 0;
    return BT_FAILURE;
}

/**
 * @brief 创建一个基本行为树节点
 *
 * @param type
 * @param bt_callback
 * @param child_count
 * @return BTNode*
 */
static BTNode *bt_Create_Node(BTNodeType type, BTStatus (*bt_callback)(BTNode *), int child_count)
{
    BTNode *node = (BTNode *)malloc(sizeof(BTNode));
    node->type = type;
    node->bt_callback = bt_callback;
    node->child_count = child_count;
    node->children = child_count > 0 ? (BTNode **)calloc(child_count, sizeof(BTNode *)) : NULL;
    node->current_index = 0;
    node->data = NULL;
    return node;
}

/**
 * @brief 创建一个组合节点
 *
 * @param type
 * @param tick
 * @param child_count
 * @return BTNode*
 */
BTNode *bt_Create_Composite_Node(BTNodeType type, int child_count)
{
    BTStatus (*tick_func)(BTNode *) = NULL;

    switch (type)
    {
    case BT_SELECTOR:
        tick_func = selector_excutor;
        break;
    case BT_SEQUENCE:
        tick_func = sequence_excutor;
        break;
    default:
        return NULL; // 非法类型
    }

    return bt_Create_Node(type, tick_func, child_count);
}

/**
 * @brief 创建一个动作节点
 *
 * @param action_func
 * @return BTNode*
 */
BTNode *bt_Create_Action_Node(BTStatus (*action_func)(BTNode *))
{
    return bt_Create_Node(BT_ACTION, action_func, 0);
}

/**
 * @brief 执行行为树
 *
 * @param root
 * @return BTStatus
 */
BTStatus bt_Execute_Tree(BTNode *root)
{
    if (root == NULL)
    {
        return BT_FAILURE; // 根节点为空，执行失败
    }

    return root->bt_callback(root); // 执行根节点的函数
}

/**
 * @brief 添加子节点到父节点
 *
 * @param parent 父节点
 * @param child 子节点
 * @param child_index 子节点索引
 */
void bt_Add_Child(BTNode *parent, BTNode *child, int child_index)
{
    if (parent->children[child_index] == NULL && child_index < parent->child_count)
    {
        parent->children[child_index] = child;
        child->current_index = child_index; // 设置子节点的索引
        return;
    }
}
