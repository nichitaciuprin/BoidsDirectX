// ==++==
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// ==--==
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
//
// threadscheduler.h
//
// Header file containing the metaphor for a thread based concrt scheduler
//
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
#pragma once

#pragma warning (push)
#pragma warning (disable: 4100) // unreferenced formal parameter, for comments

namespace Concurrency
{
namespace details
{
    class ThreadScheduler : public IScheduler, public SchedulerBase
    {
    public:

        /// <summary>
        ///     Creates a thread based scheduler
        /// </summary>
        ThreadScheduler(_In_ const ::Concurrency::SchedulerPolicy& pPolicy);

        /// <summary>
        ///     Creates a thread based scheduler
        /// </summary>
        static ThreadScheduler* Create(_In_ const ::Concurrency::SchedulerPolicy& pPolicy);

        /// <summary>
        ///     Create the correct flavor of virtual processor
        /// </summary>
        virtual VirtualProcessor *CreateVirtualProcessor(SchedulingNode *pOwningNode, IVirtualProcessorRoot *pOwningRoot);

        /// <summary>
        ///     Destroys a thread based scheduler
        /// </summary>
        virtual ~ThreadScheduler();

        /// <summary>
        ///     Returns a scheduler unique identifier for the context.
        /// </summary>
        /// <returns>
        ///     The Id for the IScheduler.
        /// </returns>
        virtual unsigned int GetId() const { return Id(); }

        /// <summary>
        ///     Get the scheduler policy.
        /// </summary>
        /// <returns>
        ///     The policy of the scheduler.
        /// </returns>
        virtual SchedulerPolicy GetPolicy() const
        {
            return SchedulerBase::GetPolicy();
        }

        /// <summary>
        ///     Called by the resource manager in order to gather statistics for a given scheduler.  The statistics gathered here
        ///     will be used to drive dynamic feedback with the scheduler to determine when it is appropriate to assign more resources
        ///     or take resources away.  Note that these counts can be optimistic and do not necessarily have to reflect the current
        ///     count with 100% synchronized accuracy.
        /// </summary>
        /// <param name="pTaskCompletionRate">
        ///     The number of tasks which have been completed by the scheduler since the last call to the Statistics method.
        /// </param>
        /// <param name="pTaskArrivalRate">
        ///     The number of tasks that have arrived in the scheduler since the last call to the Statistics method.
        /// </param>
        /// <param name="pNumberOfTasksEnqueued">
        ///     The total number of tasks in all scheduler queues.
        /// </param>
        virtual void Statistics(unsigned int *pTaskCompletionRate, unsigned int *pTaskArrivalRate, unsigned int *pNumberOfTasksEnqueued)
        {
            SchedulerBase::Statistics(pTaskCompletionRate, pTaskArrivalRate, pNumberOfTasksEnqueued);
        }

        /// <summary>
        ///     Called when the resource manager is giving virtual processors to a particular scheduler.  The virtual processors are
        ///     identified by an array of IVirtualProcessorRoot interfaces. This call is made to grant virtual processor roots
        ///     at initial allocation during the course of ISchedulerProxy::RequestInitialVirtualProcessors, and during dynamic
        ///     core migration.
        /// </summary>
        /// <param name="pVirtualProcessorRoots">
        ///     An array of IVirtualProcessorRoot interfaces representing the virtual processors being added to the scheduler.
        /// </param>
        /// <param name="count">
        ///     Number of IVirtualProcessorRoot interfaces in the array.
        /// </param>
        virtual void AddVirtualProcessors(IVirtualProcessorRoot **ppVirtualProcessorRoots, unsigned int count)
        {
            SchedulerBase::AddVirtualProcessors(ppVirtualProcessorRoots, count);
        }

        /// <summary>
        ///     Called when the resource manager is taking away virtual processors from a particular scheduler.  The scheduler should
        ///     mark the supplied virtual processors such that they are removed asynchronously and return immediately.  Note that
        ///     the scheduler should make every attempt to remove the virtual processors as quickly as possible as the resource manager
        ///     will reaffinitize threads executing upon them to other resources.  Delaying stopping the virtual processors may result
        ///     in unintentional oversubscription within the scheduler.
        /// </summary>
        /// <param name="pVirtualProcessorRoots">
        ///     An array of IVirtualProcessorRoot interfaces representing the virtual processors which are to be removed.
        /// </param>
        /// <param name="count">
        ///     Number of IVirtualProcessorRoot interfaces in the array.
        /// </param>
        virtual void RemoveVirtualProcessors(IVirtualProcessorRoot **ppVirtualProcessorRoots, unsigned int count)
        {
            SchedulerBase::RemoveVirtualProcessors(ppVirtualProcessorRoots, count);
        }

        /// <summary>
        ///     Called when the resource manager is made aware that the hardware threads underneath the virtual processors assigned to
        ///     this particular scheduler are 'externally idle' once again i.e. any other schedulers that may have been using them have
        ///     stopped using them. This API is called only when a scheduler proxy was created with MinConcurrency = MaxConcurrency.
        /// </summary>
        /// <param name="pVirtualProcessorRoots">
        ///     An array of IVirtualProcessorRoot interfaces representing the virtual processors on which other schedulers have become idle.
        /// </param>
        /// <param name="count">
        ///     Number of IVirtualProcessorRoot interfaces in the array.
        /// </param>
        virtual void NotifyResourcesExternallyIdle(IVirtualProcessorRoot ** ppVirtualProcessorRoots, unsigned int count) {}

        /// <summary>
        ///     Called when the resource manager is made aware that the execution resources underneath the virtual processors assigned to
        ///     this particular scheduler are busy (active) on other schedulers. The reason these execution resources were lent to
        ///     other schedulers is usually a lack of activation on the part of this scheduler, or a system-wide oversubscription.
        ///     This API is called only when a scheduler proxy was created with MinConcurrency = MaxConcurrency.
        /// </summary>
        /// <param name="pVirtualProcessorRoots">
        ///     An array of IVirtualProcessorRoot interfaces representing the virtual processors on which other schedulers have become busy.
        /// </param>
        /// <param name="count">
        ///     Number of IVirtualProcessorRoot interfaces in the array.
        /// </param>
        virtual void NotifyResourcesExternallyBusy(IVirtualProcessorRoot ** ppVirtualProcessorRoots, unsigned int count) {}

        /// <summary>
        ///     Returns an IScheduler interface.
        /// </summary>
        /// <returns>
        ///     An IScheduler interface.
        /// </returns>
        virtual IScheduler * GetIScheduler() { return this; }

    protected:

        ///<summary>
        ///     Creates a new thread internal context and returns it to the base scheduler.
        ///</summary>
        virtual InternalContextBase *CreateInternalContext();

    private:

        // Hide the assignment operator and copy constructor.
        ThreadScheduler const &operator =(ThreadScheduler const &);  // no assign op
        ThreadScheduler(ThreadScheduler const &);                    // no copy ctor

    };
} // namespace details
} // namespace Concurrency

#pragma warning (pop)
