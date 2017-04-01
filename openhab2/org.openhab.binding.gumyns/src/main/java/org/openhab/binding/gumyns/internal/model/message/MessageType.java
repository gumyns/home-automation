package org.openhab.binding.gumyns.internal.model.message;

public enum MessageType {
    ACK(0x100),
    UNKNOWN(0x200),
    BINDING(0x01),
    IDENT(0x02),
    JSON(0x03),
    ERROR(0xFF);

    public final int value;

    MessageType(int value) {
        this.value = value;
    }

    public static MessageType parse(int value) {
        switch (value) {
            case 0x01:
                return MessageType.BINDING;
            case 0x02:
                return MessageType.IDENT;
            case 0x03:
                return MessageType.JSON;
            case 0xFF:
                return MessageType.ERROR;
            default:
                return MessageType.UNKNOWN;
        }
    }

}
