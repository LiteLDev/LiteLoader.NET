#include <src/Header/Schedule.hpp>
#include <src/Main/PluginOwnData.hpp>

namespace LiteLoader::Schedule
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
    inline ScheduleTask^ ScheduleAPI::Delay(TaskDelegate^ task, unsigned long long tickDelay)
    {
        return Delay(task, tickDelay, nint_t(CALLING_MODULE));
    }

    inline ScheduleTask^ ScheduleAPI::Delay(TaskDelegate^ task, unsigned long long tickDelay, nint_t handle)
    {
        auto ret = gcnew ScheduleTask(::Schedule::delay(
            static_cast<void (*)(void)>(Marshal::GetFunctionPointerForDelegate(task).ToPointer()), tickDelay, (HMODULE)handle.ToPointer()));

        LiteLoader::NET::PluginOwnData::AddRegisteredSchedule(handle, ret, GCHandle::Alloc(task));

        return ret;
    }

    inline ScheduleTask^ ScheduleAPI::Repeat(TaskDelegate^ task, unsigned long long tickInterval)
    {
        return Repeat(task, tickInterval, -1);
    }

    inline ScheduleTask^ ScheduleAPI::Repeat(TaskDelegate^ task, unsigned long long tickInterval, int maxCount)
    {
        return Repeat(task, tickInterval, maxCount, nint_t(CALLING_MODULE));
    }

    inline ScheduleTask^ ScheduleAPI::Repeat(TaskDelegate^ task, unsigned long long tickInterval, int maxCount, nint_t handle)
    {
        auto ret = gcnew ScheduleTask(::Schedule::repeat(
            static_cast<void (*)(void)>(Marshal::GetFunctionPointerForDelegate(task).ToPointer()), tickInterval, maxCount, (HMODULE)handle.ToPointer()));

        LiteLoader::NET::PluginOwnData::AddRegisteredSchedule(handle, ret, GCHandle::Alloc(task));

        return ret;
    }

    inline ScheduleTask^ ScheduleAPI::DelayRepeat(TaskDelegate^ task, unsigned long long tickDelay, unsigned long long tickInterval)
    {
        return DelayRepeat(task, tickDelay, tickInterval, -1);
    }

    inline ScheduleTask^ ScheduleAPI::DelayRepeat(TaskDelegate^ task, unsigned long long tickDelay, unsigned long long tickInterval, int maxCount)
    {
        return DelayRepeat(task, tickDelay, tickInterval, maxCount, nint_t(CALLING_MODULE));
    }

    inline ScheduleTask^ ScheduleAPI::DelayRepeat(TaskDelegate^ task, unsigned long long tickDelay, unsigned long long tickInterval, int maxCount, nint_t handle)
    {
        auto ret = gcnew ScheduleTask(::Schedule::delayRepeat(
            static_cast<void (*)(void)>(Marshal::GetFunctionPointerForDelegate(task).ToPointer()), tickDelay, tickInterval, maxCount, (HMODULE)handle.ToPointer()));

        LiteLoader::NET::PluginOwnData::AddRegisteredSchedule(handle, ret, GCHandle::Alloc(task));

        return ret;
    }

    inline ScheduleTask^ ScheduleAPI::NextTick(TaskDelegate^ task)
    {
        return NextTick(task, nint_t(CALLING_MODULE));
    }

    inline ScheduleTask^ ScheduleAPI::NextTick(TaskDelegate^ task, nint_t handle)
    {
        auto ret = gcnew ScheduleTask(::Schedule::nextTick(
            static_cast<void (*)(void)>(Marshal::GetFunctionPointerForDelegate(task).ToPointer()), (HMODULE)handle.ToPointer()));

        LiteLoader::NET::PluginOwnData::AddRegisteredSchedule(handle, ret, GCHandle::Alloc(task));

        return ret;
    }

} // namespace LiteLoader::Schedule
