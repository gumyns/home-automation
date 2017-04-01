package org.openhab.binding.gumyns.internal.model.message;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;

import org.openhab.binding.gumyns.Binding;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class BindingMessage extends Message {

    private static final Logger logger = LoggerFactory.getLogger(BindingMessage.class);

    public static Message create(Binding binding) {
        ByteBuffer buffer = ByteBuffer.allocate(6);
        String[] addresses = binding.address.split(":");
        buffer.putShort(0, Short.parseShort(addresses[0]));
        buffer.putShort(2, Short.parseShort(addresses[1]));
        buffer.putShort(4, Short.parseShort(addresses[2]));
        ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
        try {
            outputStream.write(buffer.array());
            outputStream.write(binding.binding.getBytes("UTF-8"));
        } catch (IOException e) {
            logger.error("Can't prepare binding", e);
        }
        return new BindingMessage(outputStream.toByteArray());
    }

    BindingMessage(byte[] data) {
        super(MessageType.BINDING, data);
    }

}
