#ifndef AS2_TICKET_HPP
#define AS2_TICKET_HPP

#include "logger.hpp"
#include <functional>
#include <sstream>
#include <format>
#include <string>
#include <chrono>

namespace AS2 {

    enum class Category {
        NETWORK,
        SOFTWARE,
        HARDWARE,
        ACCOUNT,
        OTHER,
        UNDEFINED
    };

    inline Category category_from_string(const std::string& status) {
        if(status == "network") return Category::NETWORK;
        else if(status == "software") return Category::SOFTWARE;
        else if (status == "hardware") return Category::HARDWARE;
        else if (status == "account") return Category::ACCOUNT;
        else if (status == "other") return Category::OTHER;
        return Category::UNDEFINED;
    }

    inline std::string to_string(const Category& status) {
        switch(status) {
            case Category::NETWORK: return "network";
            case Category::SOFTWARE: return "software";
            case Category::HARDWARE: return "hardware";
            case Category::ACCOUNT: return "account";
            case Category::OTHER: return "other";
            default: return "undefined";
        }
    }

    enum class Priority {
        LOW,
        MEDIUM,
        HIGH,
        CRITICAL,
        UNDEFINED
    };

    inline Priority priority_from_string(const std::string& status) {
        if(status == "low") return Priority::LOW;
        else if(status == "medium") return Priority::MEDIUM;
        else if (status == "high") return Priority::HIGH;
        else if (status == "critical") return Priority::CRITICAL;
        return Priority::UNDEFINED;
    }

    inline std::string to_string(const Priority& status) {
        switch(status) {
            case Priority::LOW: return "low";
            case Priority::MEDIUM: return "medium";
            case Priority::HIGH: return "high";
            case Priority::CRITICAL: return "critical";
            default: return "undefined";
        }
    }

    enum class Status {
        OPEN,
        CLOSED,
        UNDEFINED
    };

    inline Status status_from_string(const std::string& status) {
        if(status == "closed") return Status::CLOSED;
        else if(status == "open") return Status::OPEN; 
        return Status::UNDEFINED;
    }

    inline std::string to_string(const Status& status) {
        switch(status) {
            case Status::CLOSED: return "closed";
            case Status::OPEN: return "open";
            default: return "undefined";
        }
    }

    class Ticket {
    private:
        size_t ticket_id {};
        std::string name {};
        std::string description {};
        
        Category category;
        Priority priority;
        Status status;

        std::chrono::utc_clock::time_point created_at;
        std::chrono::utc_clock::time_point closed_at;
    public:
        Ticket() = default;
        Ticket(std::string fullString) {
            this->parseFullTicketString(fullString);
        }

        void parseTicketString(std::string ticketStr) {
            // format is: [command]|[name]|[category]|[priority]|[desc]
            constexpr char delim { '|' };
            ticketStr.push_back(delim);

            mz::debug("[Ticket] parseTicketString parsing: " + ticketStr);
            
            const auto parseFromDelim = [&ticketStr, &delim]() -> std::string {
                const size_t delimPos { ticketStr.find_first_of(delim) };
                if(delimPos == std::string::npos) return "";

                const std::string portion { ticketStr.substr(0, delimPos) };
                
                ticketStr.erase(0, delimPos + 1);
                return portion;
            };

            // Expects 5 parses
            constexpr int number_of_delims { 5 };
            for(int i = 0; i < number_of_delims; ++i) {
                std::string res { parseFromDelim() };
                mz::debug("[Ticket] parseTicketString at index: " + std::to_string(i) + "\tParsed: " + res);

                if(res == "") throw std::runtime_error("Invalid Ticket");

                switch(i) {
                    case 1: this->name = res; break;
                    case 2: {
                        const Category _category { category_from_string(res) };
                        if(_category == Category::UNDEFINED) throw std::runtime_error("Invaild Category");

                        this->category = _category;
                        break;
                    }
                    case 3: {
                        const Priority _priority { priority_from_string(res) };
                        if(_priority == Priority::UNDEFINED) throw std::runtime_error("Invaild Status");

                        this->priority = _priority;
                        break;
                    }
                    case 4: { this->description = res; break; }
                }
            }

            // If made it this far, ticket is valid
            this->status = Status::OPEN;
            this->created_at = std::chrono::utc_clock::now();
            
            // Combine the name + time it was made in utc
            std::string hashKey { this->name + std::format("{:%Y%m%d%H%M}", this->created_at) };
            this->ticket_id = std::hash<std::string>{}(hashKey);
        }

        void parseFullTicketString(std::string ticketStr) {
            constexpr char delim { '|' };
            ticketStr.push_back(delim);

            mz::debug("[Ticket] parseFullTicketString parsing: " + ticketStr);
            
            const auto parseFromDelim = [&ticketStr, &delim]() -> std::string {
                const size_t delimPos { ticketStr.find_first_of(delim) };
                if(delimPos == std::string::npos) return "";

                const std::string portion { ticketStr.substr(0, delimPos) };
                
                ticketStr.erase(0, delimPos + 1);
                return portion;
            };


            //[ID]|[NAME]|[DESCRIPTION]|[CATEGORY]|[PRIORITY]|[STATUS]|[created_at]|[closed_at]
            this->ticket_id = std::stoull(parseFromDelim());
            this->name = parseFromDelim();
            this->description = parseFromDelim();
            this->category = AS2::category_from_string(parseFromDelim());
            this->priority = AS2::priority_from_string(parseFromDelim());
            this->status = AS2::status_from_string(parseFromDelim());
            
            std::int64_t ticks { std::stoll(parseFromDelim()) };
            this->created_at = std::chrono::utc_clock::time_point{
                std::chrono::utc_clock::duration{ticks}
            };

            const std::string& closed { parseFromDelim() };
            if(closed != "N/A") {
                ticks = std::stoll(closed);
                this->closed_at = std::chrono::utc_clock::time_point{
                    std::chrono::utc_clock::duration{ticks}
                };
            }
        }

        std::string to_raw_string() const {
            std::stringstream ss;
            ss << this->ticket_id << "|" << this->name << "|" << this->description 
                << "|" << AS2::to_string(this->category) << "|" << AS2::to_string(this->priority)
                << "|" << AS2::to_string(this->status) << "|" << std::to_string(this->created_at.time_since_epoch().count())
                << "|" << (this->closed_at == std::chrono::utc_clock::time_point{} 
                    ? "N/A" : std::to_string(this->closed_at.time_since_epoch().count()));

            return ss.str();
        }

        std::string to_string() const {
            std::stringstream ss;
            ss << "[ID]: " << this->ticket_id
                << "\n[Name]: " << this->name
                << "\n[Description]: " << this->description 
                << "\n[Category]: " << AS2::to_string(this->category)
                << "\n[Priority]: " << AS2::to_string(this->priority)
                << "\n[Status]: " << AS2::to_string(this->status)
                << "\n[created_at]: " << std::format("{:%Y%m%d%H%M}", this->created_at)
                << "\n[closed_at]: " << (this->closed_at == std::chrono::utc_clock::time_point{} 
                    ? "N/A" : std::format("{:%Y%m%d%H%M}", this->closed_at));

            return ss.str();
        }

        Priority getPriority() const { return this->priority; }
        Status getStatus() const { return this->status; }
        std::string get_name() const { return this->name; }
        std::string get_fifo_name() const { return "/tmp/ticket_notifications_" + this->name + ".fifo"; }
        size_t id() const { return this->ticket_id; }

        void close() { 
            this->status = Status::CLOSED; 
            this->closed_at = std::chrono::utc_clock::now(); 
        }

        friend std::ostream& operator<<(std::ostream& ostr, const Ticket& ticket) { 
            return ostr << ticket.to_string() << "\n"; 
        }
    };
};  

#endif