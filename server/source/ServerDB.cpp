//
// Created by denactive on 15.04.2021.
//

#include "ServerDB.h"

std::string DBServer::parse_error(const db_error& e) {
    switch(e) {
        case OK:
            return "OK";
        case invalid_command:
            return "invalid command";
        case invalid_record:
            return "invalid record";
        case no_table:
            return "no such table";
        case unsupported:
            return "unsupported command";
        case not_found:
            return "not found";
        default:
            return "unknown error";
    }
};

std::string DBServer::query(std::string q, db_error& ec) {
    for (size_t i = 0; i < q.size(); ++i) {
        if (i > 5 && q.substr(i - 5, 5) == "where")
            i = q.size();  // break 
        if ('A' <= q[i] && q[i] <= 'Z')
            q[i] += ('a' - 'A');
    }
    auto command_end = q.find(' ');
    if (command_end == std::string::npos)
        return parse_error(invalid_command);
    auto command = q.substr(0, command_end);
    std::cout << "|command|: " << command << '\n';
    if (command != "select")
        return parse_error(unsupported);

    auto target_end = q.substr(7).find(' ');
    if (target_end == std::string::npos)
        return parse_error(invalid_command);
    auto target = q.substr(7, target_end);
    std::cout << "|target |: " << target << '\n';
    if (target != "*")
        return parse_error(unsupported);

    auto from_beg = q.find("from ");
    if (from_beg == std::string::npos)
        return parse_error(invalid_command);
    auto table_end = q.substr(from_beg + 5).find(' ');
    if (table_end == std::string::npos)
        return parse_error(invalid_command);
    auto table = q.substr(from_beg + 5, table_end);
    std::cout << "|table  |: " << table << '\n';

    auto where_beg = q.find("where ");
    if (where_beg == std::string::npos)
        return parse_error(invalid_command);
    where_beg += 6;

    auto condition = q.substr(where_beg);
    auto eq = condition.find('=');
    if (eq == std::string::npos)
        return parse_error(invalid_command);
    auto param = condition.substr(0, eq);
    auto value = condition.substr(eq + 1);
    std::cout << "|param  |: " << param << '\n';
    std::cout << "|value  |: " << value << '\n';

    bool find = false;
    for (auto el : tables_)
        if (el == table)
            find = true;
    if (!find)
        return parse_error(no_table);

    std::ifstream in((doc_root_) + "/" + table + ".txt");
    if (!in.is_open()) {
        std::cout << "\tfile " << doc_root_ + "/" + table + ".txt is not opened\n";
        return parse_error(invalid_record);
    }
    std::string table_data;
    char sym = '\0';
    while (in.get(sym) && sym != EOF && sym != '\0')
        table_data += sym;

    // name
    auto required_record = table_data.find("\"" + param + "\": \"" + value);
    if (required_record == std::string::npos)
        return parse_error(not_found);

    // whole record
    auto record_pos = table_data.rfind('{', required_record);
    std::cout << "\t\trecord_pos ('{'): " << record_pos << " (" << table_data.substr(record_pos, 10) << "...)" << "\n";
    if (record_pos == std::string::npos) {
        std::cout << "\t\tnot found | invalid user record: no '{'\n";
        // logger_->log(logging_data += "not found | invalid user record: no '{'\n");
        return parse_error(invalid_record);
    }
    auto record_end_pos = table_data.substr(record_pos).find('}');
    std::cout << "\t\trecord_end_pos ('}'): " << record_end_pos << " (" << table_data.substr(record_pos + record_end_pos, 10) << "...)" << "\n";
    if (record_pos == std::string::npos) {
        std::cout << "\t\tnot found | invalid user record: no '}'\n";
        //logger_->log(logging_data += "not found | invalid user record: no '}'\n");
        return parse_error(invalid_record);
    }
    auto record = table_data.substr(record_pos, record_end_pos + 1);
    ec = db_error::OK;
    return record;
}