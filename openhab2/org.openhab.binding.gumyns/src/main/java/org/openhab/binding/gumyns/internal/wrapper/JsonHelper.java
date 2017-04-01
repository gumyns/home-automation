package org.openhab.binding.gumyns.internal.wrapper;

import java.util.Optional;

import org.eclipse.smarthome.core.library.types.DecimalType;
import org.eclipse.smarthome.core.library.types.OnOffType;
import org.eclipse.smarthome.core.library.types.OpenClosedType;
import org.eclipse.smarthome.core.types.Command;
import org.eclipse.smarthome.core.types.State;

import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonPrimitive;

public class JsonHelper {

    public static JsonArray toJson(String channel, Command command) {
        return Optional.ofNullable(convertToPrimitive(command)).map(value -> {
            JsonObject object = new JsonObject();
            object.add(channel, value);
            return object;
        }).map(object -> {
            JsonArray array = new JsonArray();
            array.add(object);
            return array;
        }).orElse(null);
    }

    private static JsonPrimitive convertToPrimitive(Command command) {
        if (command instanceof OnOffType) {
            return new JsonPrimitive(((OnOffType) command) == OnOffType.ON);
        } else if (command instanceof OpenClosedType) {
            return new JsonPrimitive(((OpenClosedType) command) == OpenClosedType.OPEN);
        }
        return null;
    }

    public static State fromJson(String type, JsonElement value) {
        switch (type) {
            case "Switch":
                return Converter.asOnOffType(value.getAsBoolean());
            case "Contact":
                return Converter.asOpenClosedType(value.getAsBoolean());
            case "Number":
                return new DecimalType(value.getAsBigDecimal());
            default:
                return null;
        }
    }
}
