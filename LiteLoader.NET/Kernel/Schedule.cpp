#include <LiteLoader.NET/Header/Schedule.hpp>
namespace LLNET::Schedule
{
ScheduleTask::ScheduleTask(::ScheduleTask& s)
{
    _this = new ::ScheduleTask(s);
}
ScheduleTask::ScheduleTask(unsigned int taskId)
{
    _this = new ::ScheduleTask(taskId);
}
ScheduleTask::!ScheduleTask()
{
    delete _this;
}
ScheduleTask::~ScheduleTask()
{
    this->!ScheduleTask();
}
bool ScheduleTask::Cancel()
{
    return _this->cancel();
}
unsigned int ScheduleTask::TaskId::get()
{
    return _this->getTaskId();
}
inline ScheduleTask ^ ScheduleAPI::Delay(TaskDelegate ^ task, unsigned long long tickDelay)
{
    GCHandle::Alloc(task);
    return Delay(task, tickDelay, System::IntPtr(GlobalClass::GetCurrentModule(Assembly::GetCallingAssembly())));
}

inline ScheduleTask ^ ScheduleAPI::Delay(TaskDelegate ^ task, unsigned long long tickDelay, System::IntPtr handle)
{
    GCHandle::Alloc(task);
    return gcnew ScheduleTask(::Schedule::delay(
        static_cast<void (*)(void)>(Marshal::GetFunctionPointerForDelegate(task).ToPointer()), tickDelay, (HMODULE)(void*)handle));
}

inline ScheduleTask ^ ScheduleAPI::Repeat(TaskDelegate ^ task, unsigned long long tickInterval)
{
    GCHandle::Alloc(task);
    return Repeat(task, tickInterval, -1);
}

inline ScheduleTask ^ ScheduleAPI::Repeat(TaskDelegate ^ task, unsigned long long tickInterval, int maxCount)
{
    GCHandle::Alloc(task);
    return Repeat(task, tickInterval, maxCount, System::IntPtr(GlobalClass::GetCurrentModule(Assembly::GetCallingAssembly())));
}

inline ScheduleTask ^ ScheduleAPI::Repeat(TaskDelegate ^ task, unsigned long long tickInterval, int maxCount, System::IntPtr handle)
{
    GCHandle::Alloc(task);
    return gcnew ScheduleTask(::Schedule::repeat(
        static_cast<void (*)(void)>(Marshal::GetFunctionPointerForDelegate(task).ToPointer()), tickInterval, maxCount, (HMODULE)(void*)handle));
}

inline ScheduleTask ^ ScheduleAPI::DelayRepeat(TaskDelegate ^ task, unsigned long long tickDelay, unsigned long long tickInterval)
{
    GCHandle::Alloc(task);
    return DelayRepeat(task, tickDelay, tickInterval, -1);
}

inline ScheduleTask ^ ScheduleAPI::DelayRepeat(TaskDelegate ^ task, unsigned long long tickDelay, unsigned long long tickInterval, int maxCount)
{
    GCHandle::Alloc(task);
    return DelayRepeat(task, tickDelay, tickInterval, maxCount, System::IntPtr(GlobalClass::GetCurrentModule(Assembly::GetCallingAssembly())));
}

inline ScheduleTask ^ ScheduleAPI::DelayRepeat(TaskDelegate ^ task, unsigned long long tickDelay, unsigned long long tickInterval, int maxCount, System::IntPtr handle)
{
    GCHandle::Alloc(task);
    return gcnew ScheduleTask(::Schedule::delayRepeat(
        static_cast<void (*)(void)>(Marshal::GetFunctionPointerForDelegate(task).ToPointer()), tickDelay, tickInterval, maxCount, (HMODULE)(void*)handle));
}

inline ScheduleTask ^ ScheduleAPI::NextTick(TaskDelegate ^ task)
{
    GCHandle::Alloc(task);
    return NextTick(task, System::IntPtr(GlobalClass::GetCurrentModule(Assembly::GetCallingAssembly())));
}

inline ScheduleTask ^ ScheduleAPI::NextTick(TaskDelegate ^ task, System::IntPtr handle)
{
    GCHandle::Alloc(task);
    return gcnew ScheduleTask(::Schedule::nextTick(
        static_cast<void (*)(void)>(Marshal::GetFunctionPointerForDelegate(task).ToPointer()), (HMODULE)(void*)handle));
}

} // namespace LLNET::Schedule