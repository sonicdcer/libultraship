#pragma once

#include "libultraship/color.h"
#include <nlohmann/json.hpp>
#include <stdint.h>
#include <memory>
#include <unordered_map>
#include <string>

namespace Ship {
typedef enum class ConsoleVariableType { Integer, Float, String, Color, Color24 } ConsoleVariableType;

typedef struct CVar {
    ConsoleVariableType Type;
    union {
        int32_t Integer;
        float Float;
        char* String = nullptr;
        Color_RGBA8 Color;
        Color_RGB8 Color24;
    };
    ~CVar() {
        if (Type == ConsoleVariableType::String && String != nullptr) {
            free(String);
        }
    }
} CVar;

class ConsoleVariable {
  public:
    ConsoleVariable();
    ~ConsoleVariable();

    std::shared_ptr<CVar> Get(const char* name);

    int32_t GetInteger(const char* name, int32_t defaultValue);
    float GetFloat(const char* name, float defaultValue);
    const char* GetString(const char* name, const char* defaultValue);
    Color_RGBA8 GetColor(const char* name, Color_RGBA8 defaultValue);
    Color_RGB8 GetColor24(const char* name, Color_RGB8 defaultValue);

    void SetInteger(const char* name, int32_t value);
    void SetFloat(const char* name, float value);
    void SetString(const char* name, const char* value);
    void SetColor(const char* name, Color_RGBA8 value);
    void SetColor24(const char* name, Color_RGB8 value);

    void RegisterInteger(const char* name, int32_t defaultValue);
    void RegisterFloat(const char* name, float defaultValue);
    void RegisterString(const char* name, const char* defaultValue);
    void RegisterColor(const char* name, Color_RGBA8 defaultValue);
    void RegisterColor24(const char* name, Color_RGB8 defaultValue);

    void ClearVariable(const char* name);
    void ClearBlock(const char* name);
    void CopyVariable(const char* from, const char* to);

    void Save();
    void Load();

  protected:
    void LoadFromPath(std::string path,
                      nlohmann::detail::iteration_proxy<nlohmann::detail::iter_impl<nlohmann::json>> items);
    void LoadLegacy();

  private:
    std::unordered_map<std::string, std::shared_ptr<CVar>> mVariables;
};
} // namespace Ship
