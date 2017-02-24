//
// Created by 杨旭磊 on 2017/2/24.
//

#include "json_write.h"

using  namespace std;

void json_write::Indent ()
{
    for (int i = 0, s = initialIndentDepth + depth.size (); i < s; i++)
        Write () << indent;
}

//如果是数组就用 '[]' ,对象用‘{}’

void json_write::StartContainer (ContainerType type, ContainerLayout layout)
{
    if (forceDefaultContainerLayout) {
        layout = defaultContainerLayout;
    } else if (layout == CONTAINER_LAYOUT_INHERIT) {
        if (depth.size () > 0)
            layout = depth.top ()->layout;
        else
            layout = defaultContainerLayout;
    }

    StartChild ();
    depth.push (new Container (type, layout));
    Write () << (type == CONTAINER_TYPE_OBJECT ? '{' : '[');
}

//容器结束时需要添加 ']' 或者 ’}‘
void json_write::EndContainer ()
{
    Container *container = depth.top ();
    depth.pop ();

    if (container->childCount > 0) {
        if (container->layout == CONTAINER_LAYOUT_MULTI_LINE) {
            Write () << endl;
            Indent ();
        } else {
            Write () << containerPadding;
        }
    }

    Write () << (container->type == CONTAINER_TYPE_OBJECT ? '}' : ']');

    delete container;
}

//用于对象，元素，键值的缩进和标点符号问题
void json_write::StartChild (bool isKey)
{
    if (depth.size () == 0) {
        if (initialIndentDepth > 0)
            Indent ();
        return;
    }

    Container *container = depth.top ();
    if (container->childCount > 0 && (
            container->type == CONTAINER_TYPE_ARRAY ||
            (container->type == CONTAINER_TYPE_OBJECT && !container->isKey))) {
        Write () << ",";
        if (container->layout == CONTAINER_LAYOUT_SINGLE_LINE) {
            Write () << containerPadding;
        } else {
            Write () << endl;
            Indent ();
        }
    } else if (container->childCount == 0) {
        Write () << containerPadding;
        if (container->layout == CONTAINER_LAYOUT_MULTI_LINE) {
            Write () << endl;
            Indent ();
        }
    }

    container->isKey = isKey;
    container->childCount++;
}

//字符串需要手动添加符号，并且需要考虑转义字符
void json_write::WriteString (const char *str)
{
    Write () << "\"";
    for (int i = 0; str [i] != 0; i++)
        WriteEscapedChar (str [i]);
    Write () << "\"";
}
void json_write::WriteEscapedChar (char c)
{
    switch (c) {
        case '"': Write () << "\\\""; break;
        case '\\': Write () << "\\\\"; break;
        case '\b': Write () << "\\b"; break;
        case '\f': Write () << "\\f"; break;
        case '\n': Write () << "\\n"; break;
        case '\r': Write () << "\\r"; break;
        case '\t': Write () << "\\t"; break;
        default: Write () << c; break;
    }
}

void json_write::Value (const char *value)
{
    StartChild ();
    WriteString (value);
}

void json_write::Value (string value)
{
    StartChild ();
    WriteString (value.c_str ());
}

void json_write::Value (bool value)
{
    StartChild ();
    Write () << (value ? "true" : "false");
}
void json_write::Key (const char *key)
{
    StartChild (true);
    WriteString (key);
    Write () << keyPaddingLeft << ":" << keyPaddingRight;
}

void json_write::NullValue ()
{
    StartChild ();
    Write () << "null";
}

