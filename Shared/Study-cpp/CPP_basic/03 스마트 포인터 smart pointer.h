#pragma once

#include <memory>

namespace c17_smart_pointer
{
	void smart_pointer_test()
	{
		{
			std::unique_ptr<int> unique_ptr = std::make_unique<int>();
			std::unique_ptr<int> move_target = std::move(unique_ptr);
		}

		{
			std::weak_ptr<int> weak_ptr;
			{
				std::shared_ptr<int> shared_ptr = std::make_shared<int>();
				std::shared_ptr<int> shared = shared_ptr;
				weak_ptr = shared_ptr;
			}
			// weak_ptr이 삭제되지 않았다.
		}
	}
}