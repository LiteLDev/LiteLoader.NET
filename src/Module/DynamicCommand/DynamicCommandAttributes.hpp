#pragma once
#include <src/Main/DotNETGlobal.hpp>
#include <src/Module/DynamicCommand/DynamicCommand.hpp>

namespace LiteLoader::DynamicCommand {
    using System::AttributeUsageAttribute;
    using System::AttributeTargets;
    using System::Attribute;


    [AttributeUsage(AttributeTargets::Class)]
    /// <summary>
    /// Provides registration info for a command class.
    /// </summary>
    public ref class CommandAttribute :Attribute
    {
    public:
        /// <param name="name">－Command name, lower-case only.</param>
        CommandAttribute(String^ name)
            :Name(name)
        {
        }
        /// <summary>
        /// Command name, lower-case only.
        /// </summary>
        String^ Name;

        /// <summary>
        /// Command description.
        /// </summary>
        String^ Description = String::Empty;

        /// <summary>
        /// Command execution permission.
        /// </summary>
        MC::CommandPermissionLevel Permission = MC::CommandPermissionLevel::GameMasters;

        /// <summary>
        /// Command Alia.
        /// </summary>
        String^ Alia = String::Empty;

        /// <summary>
        /// These command parameters will be reset after excuted by creating a new instance.
        /// </summary>
        bool AutoReset = false;

        MC::CommandFlagValue Flag1 = MC::CommandFlagValue(0x80);
        MC::CommandFlagValue Flag2 = MC::CommandFlagValue(0);
    };



    [AttributeUsage(AttributeTargets::Class, AllowMultiple = true)]
    /// <summary>
    /// Set command alias by attribute.
    /// </summary>
    public ref class CommandAliasAttribute :Attribute
    {
    public:
        /// <summary>
        /// 
        /// </summary>
        /// /// <param name="alia">－Command Alia.</param>
        CommandAliasAttribute(String^ alia)
            :Alia(alia)
        {
        }

        /// <summary>
        /// Command Alia.
        /// </summary>
        String^ Alia = String::Empty;
    };

    [AttributeUsage(AttributeTargets::Enum)]
    /// <summary>
    /// Indicates that a enum will be registered.
    /// </summary>
    public ref class CommandEnumAttribute :Attribute
    {
    };



    [AttributeUsage(AttributeTargets::Field | AttributeTargets::Property)]
    /// <summary>
    /// Indicates that a field or property will be registered.
    /// </summary>
    public ref class CommandParameterAttribute :Attribute
    {
    public:
        /// <summary>
        /// 
        /// </summary>
        /// <param name="paramType">
        /// <para>－Command parameter type.</para>
        /// <para>Please check the parameter type, or you will get a cute exception.</para>
        /// </param>
        CommandParameterAttribute(DynamicCommand::ParameterType paramType)
            :Type(paramType) {}

        /// <summary>
        /// Command parameter type.
        /// </summary>
        DynamicCommand::ParameterType Type;

        /// <summary>
        /// Indicates whether this parameter is mandatory or not.
        /// </summary>
        bool IsMandatory = true;

        /// <summary>
        /// QAQ
        /// </summary>
        String^ Identifier = String::Empty;

        /// <summary>
        /// Command parameter option.
        /// </summary>
        MC::CommandParameterOption Option = MC::CommandParameterOption::None;

        /// <summary>
        /// Indicates the parameter overload id.
        /// </summary>
        property int OverloadId {int get() { return overloadId; } void set(int value) { isSet = true; overloadId = value; }}

    internal:
        int overloadId = 0;
        bool isSet = false;
    };



    [AttributeUsage(AttributeTargets::Field | AttributeTargets::Property, AllowMultiple = true)]
    /// <summary>
    /// Indicates the parameter overload id.
    /// </summary>
    public ref class CommandParameterOverloadAttribute :Attribute
    {
    public:
        /// <summary>
        /// Command parameter overload id.
        /// </summary>
        CommandParameterOverloadAttribute(int id)
            :OverloadId(id) {}

        /// <summary>
        /// Command parameter overload id.
        /// </summary>
        int OverloadId;
    };

    [AttributeUsage(AttributeTargets::Class)]
    /// <summary>
    /// Indicates that the command has empty overload.
    /// </summary>
    public ref class CommandEmptyOverloadAttribute :Attribute
    {
    };
}
