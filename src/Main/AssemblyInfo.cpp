using namespace System::Reflection;
using namespace System::Runtime::CompilerServices;
using namespace System::Runtime::InteropServices;

#include "Version.hpp"

// 有关程序集的一般信息由以下
// 控制。更改这些特性值可修改
// 与程序集关联的信息。
[assembly:AssemblyTitle(LLNET_INFO_LOADER_NAME)];
[assembly:AssemblyDescription(LLNET_INFO_LOADER_DESCRIPTION)] ;
[assembly:AssemblyConfiguration("")] ;
[assembly:AssemblyCompany(LLNET_INFO_AUTHOR)] ;
[assembly:AssemblyProduct(LLNET_INFO_LOADER_NAME)] ;
[assembly:AssemblyCopyright(LLNET_INFO_COPYRIGHT)] ;
[assembly:AssemblyTrademark("")] ;
[assembly:AssemblyCulture("")] ;

// 将 ComVisible 设置为 false 会使此程序集中的类型
//对 COM 组件不可见。如果需要从 COM 访问此程序集中的类型
//请将此类型的 ComVisible 特性设置为 true。
[assembly:ComVisible(false)];

// 如果此项目向 COM 公开，则下列 GUID 用于类型库的 ID
[assembly:Guid("992AD8D6-3EC3-27B3-5138-9DBE0F04ADE9")] ;

// 程序集的版本信息由下列四个值组成:
//
//      主版本
//      次版本
//      生成号
//      修订号
//
//可以指定所有这些值，也可以使用“生成号”和“修订号”的默认值
//通过使用 "*"，如下所示:
// [assembly: AssemblyVersion("1.0.*")]
[assembly:AssemblyVersion(LLNET_ASSEMBLY_VERSION)];
[assembly:AssemblyFileVersion(LLNET_ASSEMBLY_FILE_VERSION)] ;
