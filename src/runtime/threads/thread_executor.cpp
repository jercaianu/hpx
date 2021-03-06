//  Copyright (c) 2007-2013 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_fwd.hpp>
#include <hpx/runtime/threads/thread_executor.hpp>
#include <hpx/runtime/threads/executors/default_executor.hpp>
#include <hpx/lcos/local/once.hpp>
#include <hpx/util/reinitializable_static.hpp>

#include <boost/atomic.hpp>

namespace hpx { namespace threads
{
    scheduled_executor& scheduled_executor::default_executor()
    {
        typedef util::reinitializable_static<
            executors::default_executor, tag
        > static_type;

        static_type instance;
        return instance.get();
    }

    ///////////////////////////////////////////////////////////////////////////
    boost::atomic<scheduled_executor> default_executor_instance;

    scheduled_executor default_executor()
    {
        if (!default_executor_instance.load())
        {
            scheduled_executor& default_exec =
                scheduled_executor::default_executor();
            scheduled_executor empty_exec;

            default_executor_instance.compare_exchange_strong(
                empty_exec, default_exec);
        }
        return default_executor_instance.load();
    }

    void set_default_executor(scheduled_executor executor)
    {
        default_executor_instance.store(executor);
    }
}}

