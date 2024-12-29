#ifndef SHAREDTYPES_H
#define SHAREDTYPES_H

#include <string>
#include <functional>

struct DateTime {
    int day;
    int month;
    int year;
    int hour;
    int minute;

    bool operator<(const DateTime& other) const {
        if (year != other.year)   return year < other.year;
        if (month != other.month) return month < other.month;
        if (day != other.day)     return day < other.day;
        if (hour != other.hour)   return hour < other.hour;
        return minute < other.minute;
    }

    // Add operator==
    bool operator==(const DateTime& other) const {
        return (day == other.day &&
                month == other.month &&
                year == other.year &&
                hour == other.hour &&
                minute == other.minute);
    }
};

// Provide a custom hash for DateTime
namespace std {
    template <>
    struct hash<DateTime> {
        size_t operator()(const DateTime& dt) const {
            // Combine fields into a single size_t
            // Example approach: a simplistic combination
            // (You can do a better mixing or a prime-based approach.)
            // Here, we’ll just do a bitshift-based approach:
            auto h1 = std::hash<int>()(dt.year);
            auto h2 = std::hash<int>()(dt.month);
            auto h3 = std::hash<int>()(dt.day);
            auto h4 = std::hash<int>()(dt.hour);
            auto h5 = std::hash<int>()(dt.minute);

            // Combine them (e.g., “boost::hash_combine” style)
            size_t seed = 0;
            auto combine = [&](size_t h) {
                seed ^= h + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);
            };
            combine(h1); combine(h2); combine(h3); combine(h4); combine(h5);
            return seed;
        }
    };
}

struct Appointment {
    DateTime appointmentTime;
    std::string reason;
    class Staff* doctor;  // Forward declaration for Staff
};

struct Prescription {
    DateTime dateTime;
    std::string notes;
    std::string doctorName; // To identify which doctor wrote the prescription
};

struct PostConsultationNote {
    DateTime dateTime;
    std::string notes;
    std::string doctorName; // To identify which doctor wrote the note
};

#endif // SHAREDTYPES_H
