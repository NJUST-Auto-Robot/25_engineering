/*
 * @Author: skybase
 * @Date: 2025-04-25 21:26:11
 * @LastEditors: skybase
 * @LastEditTime: 2025-04-25 23:22:31
 * @Description:  ᕕ(◠ڼ◠)ᕗ​
 * @FilePath: \undefinedc:\Users\10548\Desktop\behavior_tree\behavior_tree.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef _BEHAVIOR_TREE_H
#define _BEHAVIOR_TREE_H

typedef enum
{
    BT_SUCCESS = 0,
    BT_FAILURE,
    BT_RUNNING
} BTStatus;

typedef enum
{
    BT_SELECTOR = 0,
    BT_SEQUENCE,
    BT_ACTION
} BTNodeType;

typedef struct BTNode
{
    char *name; // 节点名称

    BTNodeType type;
    BTStatus (*bt_callback)(struct BTNode *node); // 节点回调函数

    // 构建的树结构类型
    struct BTNode **children;
    int child_count;
    int current_index; // 表示该节点在其父节点中的索引

    void *data; // 用户自定义节点数据
} BTNode;

BTNode *bt_Create_Composite_Node(BTNodeType type, int child_count);
BTNode *bt_Create_Action_Node(BTStatus (*action_func)(BTNode *));
BTStatus bt_Execute_Tree(BTNode *root);
void bt_Add_Child(BTNode *parent, BTNode *child, int child_index);

#endif
