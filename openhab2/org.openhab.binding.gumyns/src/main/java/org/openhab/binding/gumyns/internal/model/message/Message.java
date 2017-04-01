package org.openhab.binding.gumyns.internal.model.message;

public class Message {

    public final MessageType type;

    public final byte[] data;

    public Message(MessageType type) {
        this.type = type;
        this.data = new byte[0];
    }

    public Message(MessageType type, byte[] data) {
        this.type = type;
        if (data != null) {
            this.data = data;
        } else {
            this.data = new byte[0];
        }
    }

    public static Message deserialize(byte[] frame) {
        if (frame != null) {
            switch (frame.length) {
                case 0:
                    return new Message(MessageType.ACK);
                case 1:
                    return new Message(MessageType.parse(frame[0]));
                default:
                    byte[] array = new byte[frame.length - 1];
                    System.arraycopy(frame, 1, array, 0, array.length);
                    return new Message(MessageType.parse(frame[0]), array);
            }
        }
        return new Message(MessageType.UNKNOWN);
    }

    public byte[] serialize() {
        if (type == MessageType.ACK) {
            return new byte[0];
        } else {
            byte[] array = new byte[data.length + 1];
            if (data != null) {
                System.arraycopy(data, 0, array, 1, data.length);
            }
            array[0] = (byte) type.value;
            return array;
        }
    }

    @Override
    public String toString() {
        return String.format("Msg{type:%s,content:%s}", type.toString(), data != null ? new String(data) : "null");
    }

}
