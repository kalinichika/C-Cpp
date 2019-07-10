#ifndef JSONCLIENT_H
#define JSONCLIENT_H
#undef PRINT_LOG
#include "/home/student/Projects/JSON_CS/resource/net_resource.h"

namespace JSON_CS
{
/* Класс плохой клиент (возможны аналогичные атаки):
 * Set -  устанавливает на сервере значение счетчика в указанное значение
 * Get -  запрашивает у сервера значение счетчика
 * Send - отправка ПО БАЙТАМ запроса на сервер в формате JSON (длина, запрос)
 * Recv - получение ответа от сервера в формате JSON */
class client : public net_resource
{
public:
    client (int port = DEFAULT_PORT) noexcept(false);
    ~client() noexcept;
    void Connect() const noexcept(false);
    void Set(const std::string, const int) const noexcept(false);
    void Get(const std::string) const noexcept(false);
private:
    void Send(const std::string) const noexcept(false);
    void Recv(const cJSON*) const noexcept(false);
    client(const client &other) = delete;
    client(client &other) = delete;
    client operator = (const client &other) = delete;
    client operator = (client &&other) = delete;
};
}

#endif // JSONCLIENT_H
