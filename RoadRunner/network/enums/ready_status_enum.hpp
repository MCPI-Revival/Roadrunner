namespace RoadRunner {
    namespace network {
        namespace enums {
            enum class ReadyStatusEnum {
                unready = 0,
                ready_client_generation = 1,
                ready_requested_chunks = 2
            };
        }
    }
}