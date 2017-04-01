package org.openhab.binding.gumyns.internal.model.frame;

import org.openhab.binding.gumyns.internal.model.message.Message;

import com.google.gson.Gson;
import com.google.gson.annotations.SerializedName;

public class IdentFrame {

    @SerializedName("b")
    private String binding;

    IdentFrame() {
    }

    public void binding(String binding) {
        this.binding = binding;
    }

    public String binding() {
        return binding;
    }

    public static IdentFrame from(Gson gson, Message message) {
        return gson.fromJson(new String(message.data).trim(), IdentFrame.class);
    }
}
