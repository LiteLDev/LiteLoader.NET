#pragma once
#include <ScheduleAPI.h>
#include <LiteLoader.NET/Main/DotNETGlobal.hpp>
namespace LiteLoader::Schedule
{
    public ref class ScheduleTask
    {
        ::ScheduleTask* _this;

    public:
        ScheduleTask(::ScheduleTask& s);
        ScheduleTask(unsigned int taskId);
        !ScheduleTask();
        ~ScheduleTask();
        bool Cancel();
        property unsigned int TaskId
        {
            unsigned int get();
        }
    internal:
        GCHandle gch;
    };

    public delegate void TaskDelegate(void);

    public ref class ScheduleAPI __static
    {
    public:
        inline static ScheduleTask^ Delay(TaskDelegate^ task, unsigned long long tickDelay);
        inline static ScheduleTask^ Delay(TaskDelegate^ task, unsigned long long tickDelay, System::IntPtr handle);
        inline static ScheduleTask^ Repeat(TaskDelegate^ task, unsigned long long tickInterval);
        inline static ScheduleTask^ Repeat(TaskDelegate^ task, unsigned long long tickInterval, int maxCount);
        inline static ScheduleTask^ Repeat(TaskDelegate^ task, unsigned long long tickInterval, int maxCount, System::IntPtr handle);
        inline static ScheduleTask^ DelayRepeat(TaskDelegate^ task, unsigned long long tickDelay, unsigned long long tickInterval);
        inline static ScheduleTask^ DelayRepeat(TaskDelegate^ task, unsigned long long tickDelay, unsigned long long tickInterval, int maxCount);
        inline static ScheduleTask^ DelayRepeat(TaskDelegate^ task, unsigned long long tickDelay, unsigned long long tickInterval, int maxCount, System::IntPtr handle);
        inline static ScheduleTask^ NextTick(TaskDelegate^ task);
        inline static ScheduleTask^ NextTick(TaskDelegate^ task, System::IntPtr handle);
    internal:
    };
} // namespace LiteLoader::Schedule
