#ifndef FUSION_TIMER_H
#define FUSION_TIMER_H

#include <chrono>
#include <functional>
#include <map>
#include <string>
#include <vector>

namespace imu_gps::common {

/// Time statistics utility
/// NOTE: There seems to be an issue when using Timer within gtest
class Timer {
   public:
    struct TimerRecord {
        TimerRecord() = default;
        TimerRecord(const std::string& name, double time_usage) {
            func_name_ = name;
            time_usage_in_ms_.emplace_back(time_usage);
        }
        std::string func_name_;
        std::vector<double> time_usage_in_ms_;
    };

    /**
     * Evaluate and record the time taken by a function
     * @tparam F
     * @param func The function to be evaluated
     * @param func_name The name of the function being evaluated
     */
    template <class F>
    static void Evaluate(F&& func, const std::string& func_name) {
        auto t1 = std::chrono::steady_clock::now();
        std::forward<F>(func)();
        auto t2 = std::chrono::steady_clock::now();
        auto time_used = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1).count() * 1000;

        // Record the time taken
        if (records_.find(func_name) != records_.end()) {
            records_[func_name].time_usage_in_ms_.emplace_back(time_used);
        } else {
            records_.insert({func_name, TimerRecord(func_name, time_used)});
        }
    }

    /// Print the recorded times for all functions
    static void PrintAll();

    /// Write the recorded times to a file for further analysis (e.g., graphing)
    static void DumpIntoFile(const std::string& file_name);

    /// Get the average execution time of a specific function
    static double GetMeanTime(const std::string& func_name);

    /// Clear all recorded times
    static void Clear() { records_.clear(); }

   private:
    static std::map<std::string, TimerRecord> records_;
};

}  // namespace imu_gps::utils

#endif  // FUSION_TIMER_H
