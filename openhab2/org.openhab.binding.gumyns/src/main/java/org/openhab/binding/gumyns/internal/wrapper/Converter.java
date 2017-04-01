package org.openhab.binding.gumyns.internal.wrapper;

import org.eclipse.smarthome.core.library.types.OnOffType;
import org.eclipse.smarthome.core.library.types.OpenClosedType;

public class Converter {
    public static OpenClosedType asOpenClosedType(boolean v) {
        return v ? OpenClosedType.OPEN : OpenClosedType.CLOSED;
    }

    public static OnOffType asOnOffType(boolean v) {
        return v ? OnOffType.ON : OnOffType.OFF;
    }

    public static boolean asBoolean(OpenClosedType v) {
        return v == OpenClosedType.OPEN;
    }

    public static boolean asBoolean(OnOffType v) {
        return v == OnOffType.ON;
    }

    public static String ice(String name) {
        return name.substring(name.lastIndexOf(":") + 1);
    }
}
